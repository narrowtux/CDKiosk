#include "jobmanager.h"
#include <QApplication>

JobManager::JobManager(QDir workingDirectory, QObject *parent) :
    QAbstractTableModel(parent)
{
    m_workingDirectory = workingDirectory;
}

QDir JobManager::workingDirectory()
{
    return m_workingDirectory;
}

QVariant JobManager::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation == Qt::Horizontal && role == Qt::DisplayRole) {
	switch(section) {
	case 0:
	    return tr("Job");
	case 1:
	    return tr("Discs Done");
	case 2:
	    return tr("Copies");
	case 3:
	    return tr("Progress");
	case 4:
	    return tr("Status");
	}
    }
    return QVariant();
}

int JobManager::columnCount(const QModelIndex &parent) const
{
    return 5;
}

int JobManager::rowCount(const QModelIndex &parent) const
{
    return (const int)count();
}

QVariant JobManager::data(const QModelIndex &index, int role) const
{
    if(index.isValid()) {
	int i = index.row();
	Job * job = jobAt((int)i);
	if(role == Qt::DisplayRole) {
	    switch(index.column()) {
	    case 0:
		return job->name();
	    case 1:
		return job->discsDone();
	    case 2:
		return job->discsTotal();
	    case 3:
		return job->progress();
	    case 4:
		return job->status();
	    }

	}
    }
    return QVariant();
}

bool JobManager::hasJobs()
{
    return count() > 0;
}

int JobManager::count() const
{
    return m_jobQueue.count();
}

bool JobManager::hasJob(Job *job)
{
    return m_jobQueue.contains(job);
}

Job *JobManager::jobAt(int n) const
{
    if(n < count()) {
	return m_jobQueue.at(n);
    } else {
	return 0;
    }
}

void JobManager::removeJob(Job *job)
{
    int row = m_jobQueue.indexOf(job);
    beginRemoveRows(index(row, 0).parent(), row, row);
    m_jobQueue.removeAt(row);
    endRemoveRows();
}

bool JobManager::addJob(Job *job)
{
    job->setStatus(tr("Waiting"));
    int row = m_jobQueue.count();
    beginInsertRows(index(row, 0).parent(), row, row);
    m_jobQueue.append(job);
    endInsertRows();
}
