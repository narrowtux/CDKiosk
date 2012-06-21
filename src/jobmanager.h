#ifndef JOBMANAGER_H
#define JOBMANAGER_H

#include <QObject>
#include <QDir>
#include <QDebug>
#include "jobmanager/job.h";
#include <QAbstractListModel>

class JobManager : public QAbstractTableModel
{
    Q_OBJECT
public:
    explicit JobManager(QDir workingDirectory, QObject *parent = 0);
    QDir workingDirectory();
    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    
signals:
    void jobFinished(Job *job);
    void jobDiscFinished(Job *job, int discsDone, int discsTotal);
    void jobDiscProgress(Job *job, int discsDone, int discsTotal, int progress);
    void message(QString message);
    
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
    virtual bool hasJobs();
    
    /**
     * @returns the amount of jobs the manager has
     */
    virtual int count() const;
    
    /**
     * @returns if the job was found in the queue
     * @arg job the job to look for
     */
    virtual bool hasJob(Job *job);
    
    /**
     * @returns if discs are being burned
     */
    virtual bool isRunning() {return false;}
    
    /**
     * @returns the job at the position n
     **/
    virtual Job *jobAt(int n) const;
    
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    
    int columnCount(const QModelIndex &parent) const;
    
private:
    QDir m_workingDirectory;
protected:
    QQueue<Job *> m_jobQueue;
    
    void removeJob(Job *job);
    
};

#endif // JOBMANAGER_H
