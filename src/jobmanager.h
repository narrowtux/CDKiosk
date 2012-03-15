#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <QObject>
#include <JobManager/PTJobManager.h>
#include <QDir>
#include <QDebug>
#include "jobmanager/job.h";

class JobManager : public QObject
{
    Q_OBJECT
public:
    explicit JobManager(QDir workingDirectory, QObject *parent = 0);
    QDir workingDirectory();
    
signals:
    void jobFinished(Job *job);
    void jobDiscFinished(Job *job, int discsDone, int discsTotal);
    void jobDiscProgress(Job *job, int discsDone, int discsTotal, int progress);
    
public slots:
    /**
     * Appends a job to the queue.
     * @returns if the job was successfully added
     */
    virtual bool addJob(Job *job) {return false;}
    
    /**
     * Removes a job from the queue.
     * @warning this only works if the job has not started yet
     * @returns if the job could be aborted successfully
     */
    virtual bool abortJob(Job *job) {return false;}
    
    /**
     * Begins with the actual burning process.
     * @warning jobs which are currently burned can't be aborted
     * @returns if the burning process could be started
     */
    virtual bool startBurning() {return false;}
    
public:
    /**
     * @returns if the manager has jobs
     */
    virtual bool hasJobs() {return false;}
    
    /**
     * @returns the amount of jobs the manager has
     */
    virtual int count() {return 0;}
    
    /**
     * @returns if the job was found in the queue
     * @arg job the job to look for
     */
    virtual bool hasJob(Job *job) {return false;}
    
    /**
     * @returns if discs are being burned
     */
    virtual bool isRunning() {return false;}
    
private:
    QDir m_workingDirectory;
    
};

#endif // JOBMANAGER_H
