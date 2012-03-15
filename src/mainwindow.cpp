#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datefilter.h"
#include "authorfilter.h"
#include "groupfilter.h"
#include <QDesktopServices>
#include <QMessageBox>

const int MainWindow::ROLE_DATABASE_ID = Qt::UserRole + 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showHomePage();
    m_jobManager = 0;
    
    m_speechManager.load();
    m_speechManager.addFilter(new DateFilter(ui->listMonths));
    m_speechManager.addFilter(new AuthorFilter(ui->listPersons));
    m_speechManager.addFilter(new GroupFilter(ui->listCompilations));
    
    Speech *speech = new Speech();
    speech->setName("test");
    speech->setAuthor("Hans Mustermann");
    speech->setGroup("Reihe 3");
    speech->setDate(QDate(2011, 12, 5));
    m_speechManager.addSpeech(speech);
    
    speech = new Speech();
    speech->setName("test 2");
    speech->setAuthor("Hans Mustermann");
    speech->setGroup("Reihe 3");
    speech->setDate(QDate(2011, 12, 6));
    m_speechManager.addSpeech(speech);
    
    speech = new Speech();
    speech->setName("lolwut?");
    speech->setAuthor("Mr. Herpington");
    speech->setGroup("");
    speech->setDate(QDate(2011, 2, 1));
    m_speechManager.addSpeech(speech);
    
    updateChooseLists();
    updateSpeechList();
    
    m_workDirectory = QDir(QDesktopServices::storageLocation(QDesktopServices::DataLocation));
    
    connect(ui->push1Home, SIGNAL(clicked()), this, SLOT(showHomePage()));
    connect(ui->push2Choose, SIGNAL(clicked()), this, SLOT(showChoosePage()));
    connect(ui->push3Cart, SIGNAL(clicked()), this, SLOT(showCartPage()));
    connect(ui->push4Burn, SIGNAL(clicked()), this, SLOT(showBurnPage()));
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
    updateChooseLists();
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
}

void MainWindow::updateChooseLists()
{
    QStringList dates = m_speechManager.getDates();
    ui->listMonths->clear();
    ui->listMonths->addItem(tr("All"));
    ui->listMonths->addItems(dates);
    ui->listMonths->setCurrentRow(0);
    
    QStringList authors = m_speechManager.getAuthors();
    ui->listPersons->clear();
    ui->listPersons->addItem(tr("All"));
    ui->listPersons->addItems(authors);
    ui->listPersons->setCurrentRow(0);
    
    QStringList groups = m_speechManager.getGroups();
    ui->listCompilations->clear();
    ui->listCompilations->addItem(tr("All"));
    ui->listCompilations->addItems(groups);
    ui->listCompilations->addItem(tr("None"));
    ui->listCompilations->setCurrentRow(0);
    
    updateSpeechList();
}

void MainWindow::updateSpeechList()
{
    QList<Speech *> speeches = m_speechManager.getFilteredSpeeches();
    ui->listSpeeches->clear();
    foreach(Speech * speech, speeches) {
	QListWidgetItem *item = new QListWidgetItem(speech->compiledName(), ui->listSpeeches);
	item->setData(ROLE_DATABASE_ID, speech->databaseId());
	ui->listSpeeches->addItem(item);
    }
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
    QList<QListWidgetItem *> items = ui->listSpeeches->selectedItems();
    foreach(QListWidgetItem *item, items) {
	int dbId = item->data(ROLE_DATABASE_ID).toInt();
	Speech *speech = m_speechManager.speech(dbId);
	if(speech != 0) {
	    m_speechesForJob.append(speech);
	    qDebug()<<"added speech "<<speech->author();
	}
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
