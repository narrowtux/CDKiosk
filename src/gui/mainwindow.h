#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "src/speech/speechmanager.h"
#include <QtCore>
#include "src/jobmanager/jobmanager.h"
#include "src/jobmanager/job.h"
#include <QSettings>
#include <QtSql>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	static const int ROLE_DATABASE_ID;
public:
    explicit MainWindow(QSqlDatabase &db, QWidget *parent = 0);
    ~MainWindow();

    SpeechManager * speechManager();
    
    void setJobManager(JobManager *jobManager);
    JobManager *jobManager();
public slots:
    void showHomePage();
    void showChoosePage();
    void showCartPage();
    void showBurnPage();
    void cleanGui();

private slots:

    void on_pushCD_clicked();
    
    void on_pushMP3_clicked();
    
    void cleanJob();
    
    void on_pushAddToCart_clicked();
    
    void updateCart();
    
    void on_pushRemoveFromCart_clicked();
    
    void on_pushProceedToBurn_clicked();
    
    void onDiscProgress(Job *job, int discsDone, int discsTotal, int progress);
    
    void onJobDiscFinished(Job *job, int discsDone, int discsTotal);
    void onMessage(QString message);
    void onJobFinished(Job *job);
    
    void on_pushAdministration_clicked();
    
private:
    Ui::MainWindow *ui;

    SpeechManager m_speechManager;
    
    JobManager *m_jobManager;
    
    QDir m_workDirectory;
    
    Job::DiscType m_currentDiscType;
    
    QList<Speech *> m_speechesForJob;
    
    QSettings settings;
    
    QSqlDatabase m_database;
    
    QSqlRelationalTableModel *model;
};

#endif // MAINWINDOW_H
