#ifndef JOBMANAGERSIMULATOR_H
#define JOBMANAGERSIMULATOR_H
#include <QtCore>
#include "../jobmanager.h"
#include "job.h"
#include <QQueue>

class JobManagerSimulator : public JobManager
{
    Q_OBJECT
public:
    explicit JobManagerSimulator(QDir workingDirectory, QObject *parent = 0);
    
public slots:
    /**
     * Appends a job to the queue.
     * @returns if the job was successfully added
     */
    virtual bool addJob(Job *job);
    
    /**
     * Removes a job from the queue.
     * @warning this only works if the job has not started yet
     * @returns if the job could be aborted successfully
     */
    virtual bool abortJob(Job *job);
    
    /**
     * Begins with the actual burning process.
     * @warning jobs which are currently burned can't be aborted
     * @returns if the burning process could be started
     */
    virtual bool startBurning();
    
private slots:
    void onTick();
public:
    /**
     * @returns if the manager has jobs
     */
    virtual bool hasJobs();
    
    /**
     * @returns the amount of jobs the manager has
     */
    virtual int count();
    
    /**
     * @returns if the job was found in the queue
     * @arg job the job to look for
     */
    virtual bool hasJob(Job *job);
    
    /**
     * @returns if discs are being burned
     */
    virtual bool isRunning() {return m_running;}
    
private:
    QQueue<Job *> m_jobQueue;
    QTimer *m_timer;
    int m_jobProgress;
    bool m_running;
};

#endif // JOBMANAGERSIMULATOR_H
