#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "speechmanager.h"
#include <QtCore>
#include "jobmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	static const int ROLE_DATABASE_ID;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SpeechManager * speechManager();
    
    void setJobManager(JobManager *jobManager);
public slots:
    void showChoosePage();
    void showCartPage();
    void showBurnPage();
    void cleanGui();
    void updateChooseLists();
    void updateSpeechList();

private slots:

private:
    Ui::MainWindow *ui;

    SpeechManager m_speechManager;
    
    JobManager *m_jobManager;
    
    QDir m_workDirectory;
};

#endif // MAINWINDOW_H
