#include "jobmanagersimulator.h"

JobManagerSimulator::JobManagerSimulator(QDir workingDirectory, QObject *parent) : JobManager(workingDirectory, parent)
{
    m_timer = new QTimer(this);
    m_timer->setInterval(200);
    m_jobProgress = 0;
    connect(m_timer, SIGNAL(timeout()), this, SLOT(onTick()));
    m_running = false;
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
    qDebug()<<"[Simulator] Starting to burn...";
    m_timer->start();
    emit(started());
    return true;
}

void JobManagerSimulator::onTick()
{
    if(hasJobs()) {
	Job *job = m_jobQueue.first();
	int progress = job->progress() + 1;
	job->setProgress(progress);
	QModelIndex statusIndex = index(0, 4), 
		    progressIndex = index(0, 3),
		    discsDoneIndex = index(0, 1);
	if(progress == 1) {
	    job->setStatus(tr("Recording Disc %0").arg(job->discsDone() + 1));
	    emit(dataChanged(statusIndex, statusIndex));
	}
	if(progress == 70) {
	    job->setStatus(tr("Printing Disc %0").arg(job->discsDone() + 1));
	    emit(dataChanged(statusIndex, statusIndex));
	}
	emit(dataChanged(progressIndex, progressIndex));
	emit(jobDiscProgress(job, job->discsDone(), job->discsTotal(), progress));
	if(progress == 100) {
	    progress = 0;
	    int done = job->discsDone();
	    int total = job->discsTotal();
	    done ++;
	    job->setDiscsDone(done);
	    emit(dataChanged(discsDoneIndex, discsDoneIndex));
	    emit(jobDiscFinished(job, done, total));
	    if(done == total) {
		job->setStatus(tr("Done"));
		removeJob(job);
		emit(jobFinished(job));
	    }
	}
    } else {
	qDebug()<<"Stopped burning because no jobs are left";
	m_timer->stop();
	m_running = false;
	emit(stopped());
    }
}

