#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "datefilter.h"
#include "authorfilter.h"
#include "groupfilter.h"
#include <QDesktopServices>

const int MainWindow::ROLE_DATABASE_ID = Qt::UserRole + 1;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showChoosePage();
    
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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showChoosePage()
{
    ui->centralStack->setCurrentIndex(0);
}

void MainWindow::showCartPage()
{
    ui->centralStack->setCurrentIndex(1);
}

void MainWindow::showBurnPage()
{
    ui->centralStack->setCurrentIndex(2);
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
    m_jobManager = jobManager;
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
