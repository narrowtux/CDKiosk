#include "administrationwindow.h"
#include "ui_administrationwindow.h"
#include <QKeySequence>
#include <QMessageBox>
#include "databaseentrydialog.h"
#include "src/utils/utils.h"

AdministrationWindow::AdministrationWindow(MainWindow *parent) :
    QDialog(0),
    ui(new Ui::AdministrationWindow)
{
    ui->setupUi(this);
	ui->tabWidget->setCurrentIndex(0);
    ui->checkShowAdminButton->setChecked(settings.value("showAdminButton", true).toBool());
    QString password = settings.value("password", "").toString();
    ui->checkPassword->setChecked(password != "");
    ui->linePassword->setText(password);
    
    QKeySequence seq = QKeySequence::Preferences;
    
    ui->labelShortcutHint->setText(tr("You can always show this window by pressing %0").arg(seq.toString(QKeySequence::NativeText)));
	
	ui->viewDatabase->setModel(MainWindow::instance()->model());
}

AdministrationWindow::~AdministrationWindow()
{
    delete ui;
}

void AdministrationWindow::on_checkShowAdminButton_toggled(bool checked)
{
    if(checked) {
		ui->labelShortcutHint->setStyleSheet("");
    } else {
		ui->labelShortcutHint->setStyleSheet("color:red");
    }
    settings.setValue("showAdminButton", checked);
}

void AdministrationWindow::on_linePassword_editingFinished()
{
    settings.setValue("password", ui->linePassword->text());
}

void AdministrationWindow::on_checkPassword_toggled(bool checked)
{
	ui->linePassword->setEnabled(checked);
    if(!checked) {
		settings.setValue("password", "");
		ui->linePassword->setText("");
    } else {
		ui->linePassword->setFocus();
    }
}

void AdministrationWindow::on_buttonAddEntry_clicked()
{
	DatabaseEntryDialog *dialog = new DatabaseEntryDialog(-1, this);
	dialog->open();
}

void AdministrationWindow::on_buttonDeeleteEntry_clicked()
{
	QModelIndexList rows = ui->viewDatabase->selectionModel()->selectedRows();
	if(QMessageBox::question(this, tr("Delete %n item(s)?", "", rows.count()), tr("Do you want to delete %n item(s)? (Can't be undone)", "", rows.count()), (QMessageBox::StandardButtons()|=QMessageBox::Yes)|=QMessageBox::No, QMessageBox::No) == QMessageBox::Yes) {
		QSqlRelationalTableModel *model = MainWindow::instance()->model();
		QSqlQuery query;
		query.prepare("DELETE FROM `speech` WHERE s_id=:id");
		foreach(QModelIndex row, rows) {
			int id = model->data(model->index(row.row(), 0)).toInt();
			query.bindValue(":id", id);
			SQL_PREPARED_QUERY(query);
		}
		
		MainWindow::instance()->model()->select();
	}
}

void AdministrationWindow::on_buttonEditEntry_clicked()
{
    QModelIndexList rows = ui->viewDatabase->selectionModel()->selectedRows();
	if (rows.count() > 0) {
		if (rows.count() > 1) {
			QMessageBox::information(this, tr("Can't edit multiple items"), tr("Editing multiple items is not implemented at the moment."));
			return;
		} else {
			QSqlRelationalTableModel *model = MainWindow::instance()->model();
			bool ok;
			int id = model->data(model->index(rows.at(0).row(), 0)).toInt(&ok);
			if (ok) {
				DatabaseEntryDialog *editor = new DatabaseEntryDialog(id, this);
				editor->open();
			} else {
				qDebug()<<id;
			}
		}
	}
}
