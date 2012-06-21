#ifndef JOBMANAGERSIMULATOR_H
#define JOBMANAGERSIMULATOR_H
#include <QtCore>
#include "src/jobmanager/jobmanager.h"
#include "src/jobmanager/job.h"
#include <QQueue>

class JobManagerSimulator : public JobManager
{
    Q_OBJECT
public:
    explicit JobManagerSimulator(QDir workingDirectory, QObject *parent = 0);
    
public slots:
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
     * @returns if discs are being burned
     */
    virtual bool isRunning() {return m_running;}
    
private:
    QTimer *m_timer;
    int m_jobProgress;
    bool m_running;
};

#endif // JOBMANAGERSIMULATOR_H
