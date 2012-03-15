#include "jobmanagersimulator.h"

JobManagerSimulator::JobManagerSimulator(QDir workingDirectory, QObject *parent) : JobManager(workingDirectory, parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(200);
    m_jobProgress = 0;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTick()));
}

bool JobManagerSimulator::addJob(Job *job)
{
    m_jobQueue.append(job);
}

bool JobManagerSimulator::abortJob(Job *job)
{
    if(isRunning() && job == m_jobQueue.first()) {
	return false;
    } else {
	m_jobQueue.removeAll(job);
	return true;
    }
}

bool JobManagerSimulator::startBurning()
{
    m_timer->start();
}

void JobManagerSimulator::onTick()
{
    m_jobProgress ++;
    Job *job = m_jobQueue.first();
    if(m_jobProgress == 100) {
	m_jobProgress = 0;
	int done = job->discsDone();
	int total = job->discsTotal();
	done ++;
	job->setDiscsDone(done);
	if(done == total) {
	    emit(jobFinished(job));
	    m_jobQueue.pop_front();
	} else {
	    emit(jobDiscFinished(job, done, total));
	}
    } else {
	emit(jobDiscProgress(job, job->discsDone(), job->discsTotal(), m_jobProgress));
    }
}

bool JobManagerSimulator::hasJobs()
{
    return count() > 0;
}

int JobManagerSimulator::count()
{
    return m_jobQueue.count();
}

bool JobManagerSimulator::hasJob(Job *job)
{
    return m_jobQueue.contains(job);
}
