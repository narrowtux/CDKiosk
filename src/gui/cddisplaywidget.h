#ifndef CDDISPLAYWIDGET_H
#define CDDISPLAYWIDGET_H

#include <QWidget>
#include <QTimer>
#include "src/jobmanager/jobmanager.h"

class CDDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CDDisplayWidget(QWidget *parent = 0);
    Job* currentJob();
    void setJobManager(JobManager *jobManager);
signals:
    
public slots:
    void setCurrentJob(Job* job);
    void onJobDiskProgress(Job* job, int discsDone, int discsTotal, int progress);
    void onManagerStopped();
private:
    void paintEvent(QPaintEvent *);
    
    Job *m_currentJob;
    JobManager *m_jobManager;
    
};

#endif // CDDISPLAYWIDGET_H
