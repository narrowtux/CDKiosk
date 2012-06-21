#include "src/gui/mainwindow.h"
#include "ui_mainwindow.h"
#include "src/filter/datefilter.h"
#include "src/filter/authorfilter.h"
#include "src/filter/groupfilter.h"
#include <QDesktopServices>
#include <QMessageBox>
#include "administrationwindow.h"
#include <QInputDialog>
#include <QShortcut>

const int MainWindow::ROLE_DATABASE_ID = Qt::UserRole + 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    setupDatabase();
    
    showHomePage();
    
    model = new  QSqlRelationalTableModel(this, m_database);
    model->setTable("speech");
    
    model->setJoinMode(QSqlRelationalTableModel::LeftJoin);
    model->setRelation(6, QSqlRelation("person", "p_id", "p_name"));
    
    model->setHeaderData(0, Qt::Horizontal, tr("Id", "speech"));
    model->setHeaderData(1, Qt::Horizontal, tr("Name", "speech"));
    model->setHeaderData(2, Qt::Horizontal, tr("Filename", "speech"));
    model->setHeaderData(3, Qt::Horizontal, tr("Date", "speech"));
    model->setHeaderData(4, Qt::Horizontal, tr("Creation Date", "speech"));
    model->setHeaderData(5, Qt::Horizontal, tr("Duration", "speech"));
    model->setHeaderData(6, Qt::Horizontal, tr("Speaker", "speech"));
    
    ui->viewSpeeches->setModel(model);
    ui->viewSpeeches->hideColumn(0);
    ui->viewSpeeches->hideColumn(2);
    ui->viewSpeeches->hideColumn(4);
    
    if(!model->select()) {
	qDebug()<<model->lastError();
    }
    
    m_jobManager = 0;
    
    m_workDirectory = QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    
    connect(ui->push1Home, SIGNAL(clicked()), this, SLOT(showHomePage()));
    connect(ui->push2Choose, SIGNAL(clicked()), this, SLOT(showChoosePage()));
    connect(ui->push3Cart, SIGNAL(clicked()), this, SLOT(showCartPage()));
    connect(ui->push4Burn, SIGNAL(clicked()), this, SLOT(showBurnPage()));
    
    ui->pushAdministration->setVisible(settings.value("showAdminButton", true).toBool());
    
    QShortcut *preferencesShortcut = new QShortcut(QKeySequence::Preferences, this);
    connect(preferencesShortcut, SIGNAL(activated()), this, SLOT(on_pushAdministration_clicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::showHomePage()
{
    ui->centralStack->setCurrentIndex(0);
    ui->push1Home->setChecked(true);
}


void MainWindow::showChoosePage()
{
    ui->centralStack->setCurrentIndex(1);
    ui->push2Choose->setChecked(true);
}

void MainWindow::showCartPage()
{
    ui->centralStack->setCurrentIndex(2);
    ui->push3Cart->setChecked(true);
}

void MainWindow::showBurnPage()
{
    ui->centralStack->setCurrentIndex(3);
    ui->push4Burn->setChecked(true);
}

void MainWindow::cleanGui()
{
    
}

SpeechManager * MainWindow::speechManager()
{
    return &m_speechManager;
}

void MainWindow::setJobManager(JobManager *jobManager)
{
    if(m_jobManager != 0) {
	m_jobManager->disconnect(this, SLOT(onDiscProgress(Job*,int,int,int)));
	m_jobManager->disconnect(this, SLOT(onJobDiscFinished(Job*,int,int)));
	m_jobManager->disconnect(this, SLOT(onMessage(QString)));
	m_jobManager->disconnect(this, SLOT(onJobFinished(Job*)));
    }
    m_jobManager = jobManager;
    ui->listjobs->setModel(m_jobManager);
    connect(m_jobManager, SIGNAL(jobDiscProgress(Job*,int,int,int)), this, SLOT(onDiscProgress(Job*,int,int,int)));
    connect(m_jobManager, SIGNAL(jobDiscFinished(Job*,int,int)), this, SLOT(onJobDiscFinished(Job*,int,int)));
    connect(m_jobManager, SIGNAL(jobFinished(Job*)), this, SLOT(onJobFinished(Job*)));
    connect(m_jobManager, SIGNAL(message(QString)), this, SLOT(onMessage(QString)));
    
    ui->jobVisualisation->setJobManager(jobManager);
}

JobManager *MainWindow::jobManager()
{
    return m_jobManager;
}

void MainWindow::on_pushCD_clicked()
{
    cleanJob();
    showChoosePage();
    m_currentDiscType = Job::AUDIO;
}

void MainWindow::on_pushMP3_clicked()
{
    cleanJob();
    showChoosePage();
    m_currentDiscType = Job::FILES;
}

void MainWindow::cleanJob()
{
    m_currentDiscType = Job::AUDIO;
    m_speechesForJob.clear();
}

void MainWindow::on_pushAddToCart_clicked()
{
    QModelIndexList items = ui->viewSpeeches->selectionModel()->selectedRows();
    foreach (QModelIndex item, items) {
	QSqlRecord record = model->record(item.row());
	int databaseId = record.field("s_id").value().toInt();
	QString name = record.field("s_name").value().toString();
	QString speaker = record.field("p_name").value().toString();
	QDate date = record.field("s_spoken").value().toDate();
	QString file = record.field("s_filename").value().toString();
	
	Speech *speech = new Speech();
	speech->setAuthor(speaker);
	speech->setName(name);
	speech->setDate(date);
	speech->setDatabaseId(databaseId);
	speech->setFilenameMP3(file);
	
	m_speechesForJob.append(speech);
    }
    updateCart();
}

void MainWindow::updateCart()
{
    ui->listCart->clear();
    foreach(Speech *speech, m_speechesForJob) {
	QListWidgetItem *item = new QListWidgetItem(speech->compiledName());
	item->setData(ROLE_DATABASE_ID, speech->databaseId());
	ui->listCart->addItem(item);
    }
}

void MainWindow::on_pushRemoveFromCart_clicked()
{
    QList<QListWidgetItem *> items = ui->listCart->selectedItems();
    foreach(QListWidgetItem *item, items) {
	int dbId = item->data(ROLE_DATABASE_ID).toInt();
	Speech *speech = m_speechManager.speech(dbId);
	if(speech != 0) {
	    m_speechesForJob.removeAll(speech);
	    qDebug()<<"removed speech "<<speech->author();
	}
    }
    updateCart();
}

void MainWindow::on_pushProceedToBurn_clicked()
{
    if(m_currentDiscType == Job::AUDIO) {
	foreach(Speech *speech, m_speechesForJob) {
	    Job *job = new Job();
	    job->setDiscType(m_currentDiscType);
	    FileList files;
	    files << speech->filenameMP3();
	    job->setFiles(files);
	    m_jobManager->addJob(job);
	}
    } else {
	Job *job = new Job();
	job->setDiscType(m_currentDiscType);
	FileList files;
	foreach(Speech *speech, m_speechesForJob) {
	    files << speech->filenameMP3();
	}
	job->setFiles(files);
	m_jobManager->addJob(job);
    }
    
    if(!m_jobManager->isRunning()) {
	if(!m_jobManager->startBurning()) {
	    QMessageBox::warning(this, tr("Error occured"), tr("Could not begin burning disks"));
	}
    }
    cleanJob();
    updateCart();
}

void MainWindow::onDiscProgress(Job *job, int discsDone, int discsTotal, int progress)
{
    ui->progressBar->setValue(progress);
    ui->labelJobProgress->setText(tr("%0% Progress, %1 of %2 discs done.").arg(progress).arg(discsDone).arg(discsTotal));
}

void MainWindow::onJobDiscFinished(Job *job, int discsDone, int discsTotal)
{
    ui->progressBar->setValue(100);
    ui->labelJobProgress->setText(tr("%0 of %1 discs done.").arg(discsDone).arg(discsTotal));
}

void MainWindow::onMessage(QString message)
{
    ui->labelJobProgress->setText(message);
}

void MainWindow::onJobFinished(Job *job)
{
    ui->progressBar->setValue(100);
    ui->labelJobProgress->setText(tr("Job done."));
}

void MainWindow::on_pushAdministration_clicked()
{
    QString realPassword = settings.value("password", "").toString();
    if(realPassword != "") {
	bool ok;
	QString password = QInputDialog::getText(this, tr("Password protection"), tr("Enter the admin password"), QLineEdit::Password, "", &ok);
	if(ok && password != realPassword) {
	    QMessageBox::warning(this, tr("Password wrong"), tr("The password you entered was wrong. Try again?"));
	    return;
	} else if (!ok) {
	    return;
	}
    }
    
    AdministrationWindow *window = new AdministrationWindow(this);
    window->setWindowRole("Preferences");
    window->setWindowFlags(Qt::Window);
    window->setWindowTitle(tr("Administration"));
    window->show();
}

void MainWindow::setupDatabase()
{
    m_database = QSqlDatabase::addDatabase("QMYSQL");
    
    m_database.setHostName("localhost");
    m_database.setConnectOptions("UNIX_SOCKET=/Applications/XAMPP/xamppfiles/var/mysql/mysql.sock");
    m_database.setUserName("root");
    m_database.setPassword("");
    m_database.setDatabaseName("cdkiosk");
    
    if(!m_database.open()) {
	qDebug()<<m_database.lastError();
    }
}
