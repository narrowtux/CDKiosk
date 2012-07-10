#include "databaseentrydialog.h"
#include "ui_databaseentrydialog.h"
#include <QFileDialog>
#include <QSettings>
#include <QDesktopServices>
#include <QtDebug>
#include <QtSql>
#include "src/utils/utils.h"
#include <QMessageBox>
#include "mainwindow.h"

DatabaseEntryDialog::DatabaseEntryDialog(int id, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DatabaseEntryDialog)
{
	ui->setupUi(this);
	this->m_databaseId = id;
	this->m_currentFileDialog = 0;
	
	QMap<int, QString> names;
	
	// Init Speakers from Database
	QSqlQuery speakers;
	SQL_QUERY(speakers, "SELECT p_name FROM `speaker` LEFT JOIN person ON s_id = p_id ORDER BY p_name") {
		QStringList speakerList;
		int i = 0;
		while (speakers.next()) {
			speakerList << speakers.value(0).toString();
			names.insert(i, speakers.value(0).toString());
			i++;
		}
		ui->lineSpeaker->insertItems(0, speakerList);
	}
	
	if (m_databaseId != -1) {
		QSqlQuery query;
		query.prepare("SELECT * FROM `speech` LEFT JOIN `person` ON p_id = s_speaker WHERE `s_id`=:id");
		query.bindValue(":id", id);
		if(query.exec() && query.next()) {
			ui->lineTitle->setText(query.record().value("s_name").toString());
			ui->lineSpeaker->setCurrentIndex(names.key(query.record().value("p_name").toString()));
			ui->selectDate->setSelectedDate(query.record().value("s_spoken").toDate());
			ui->timeDuration->setTime(query.record().value("s_duration").toTime());
			m_fileLocation = query.record().value("s_filename").toString();
			
			updateFileButton();
		} else {
			qDebug() << query.lastQuery() << query.lastError();
			deleteLater();
		}
	}
	
}

DatabaseEntryDialog::~DatabaseEntryDialog()
{
	delete ui;
}

void DatabaseEntryDialog::onFileDialogClosed()
{
	if (m_currentFileDialog->result() != 0) {
		m_fileLocation = m_currentFileDialog->selectedFiles().at(0);
		QFileInfo info(m_fileLocation);
		QSettings settings;
		settings.setValue("lastDataLocation", info.absoluteDir().canonicalPath());
		updateFileButton();
		ui->lineTitle->setText(info.baseName());
		//TODO parse file for duration
	}
	this->raise();
	this->activateWindow();
}

void DatabaseEntryDialog::on_buttonSelectFile_clicked()
{
	QSettings settings;
	QString dir = settings.value("lastDataLocation", QDesktopServices::storageLocation(QDesktopServices::DocumentsLocation)).toString();
	
	m_currentFileDialog = new QFileDialog(this, tr("Select File"), dir, tr("MP3-Files (*.mp3)"));
	m_currentFileDialog->setAcceptMode(QFileDialog::AcceptOpen);
	connect(m_currentFileDialog, SIGNAL(finished(int)), this, SLOT(onFileDialogClosed()));
	m_currentFileDialog->open();
}

void DatabaseEntryDialog::on_buttonToday_clicked()
{
    ui->selectDate->setSelectedDate(QDate::currentDate());
}

void DatabaseEntryDialog::on_buttonBox_accepted()
{
	int s_id = -1;
	QString speakerName = ui->lineSpeaker->currentText();
	QSqlQuery speakerId;
	SQL_QUERY(speakerId, QString("SELECT s_id FROM `speaker` LEFT JOIN person ON s_id = p_id WHERE p_name = '%0'").arg(speakerName)) {
		if (speakerId.next()) {
			s_id = speakerId.value(0).toInt();
		} else {
			QSqlQuery query;
			SQL_QUERY(query, QString("SELECT p_id FROM `person` WHERE p_name = '%0'").arg(speakerName)) {
				if (query.next()) {
					s_id = query.value(0).toInt();
					qDebug() << "found in person table"<<s_id;
				} else {
					QSqlQuery query;
					SQL_QUERY(query, QString("INSERT INTO `person` (p_name) VALUES('%0')").arg(speakerName)) {
						s_id = query.lastInsertId().toInt();
						qDebug() << "inserted new entry into person table"<<s_id;
					}
				}
			}
			
			if (s_id != -1) {
				QSqlQuery query;
				if (!query.exec(QString("INSERT INTO `speaker` (s_id) VALUES('%0')").arg(s_id))) {
					qDebug() << query.lastQuery() << query.lastError().databaseText();
					QMessageBox::critical(0, tr("Could not add speaker"), tr("Couldn't add speaker \"%0\".").arg(speakerName));
					s_id = -1;
				}
			} else {
				QMessageBox::critical(0, tr("Could not add speaker"), tr("Couldn't add speaker \"%0\".").arg(speakerName));
				s_id = -1;
			}
		}
	}
	
	QSqlQuery query;
	if(m_databaseId == -1) {
		query.prepare("INSERT INTO `speech` (s_name, s_filename, s_spoken, s_duration, s_speaker) VALUES(:title, :file, :spoken, :duration, :speaker);");
	} else {
		query.prepare("UPDATE `speech` SET s_name = :title, s_filename = :file, s_spoken = :spoken, s_duration = :duration, s_speaker = :speaker WHERE s_id = :id");
		query.bindValue(":id", m_databaseId);
	}
	query.bindValue(":title", ui->lineTitle->text());
	query.bindValue(":file", m_fileLocation);
	query.bindValue(":spoken", ui->selectDate->selectedDate());
	query.bindValue(":duration", ui->timeDuration->time());
	query.bindValue(":speaker", s_id);
	SQL_PREPARED_QUERY(query);
	
	MainWindow::instance()->model()->select();
}

void DatabaseEntryDialog::updateFileButton()
{
	if(m_fileLocation.isEmpty()) {
		ui->buttonSelectFile->setText(tr("Select File ..."));
	} else {
		QFileInfo info(m_fileLocation);
		ui->buttonSelectFile->setText(tr("[%0] ...").arg(info.baseName()));
	}
}
