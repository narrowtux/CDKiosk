#include "job.h"

Job::Job(QObject *parent) :
    QObject(parent)
{
    m_discsDone = 0;
    m_discsTotal = 1;
    m_discType = AUDIO;
    m_name = tr("untitled job");
    m_progress = 0;
    m_status = tr("Not in queue");
}

int Job::discsDone()
{
    return m_discsDone;
}

int Job::discsTotal()
{
    return m_discsTotal;
}

void Job::setDiscsDone(int d)
{
    m_discsDone = d;
}

void Job::setDiscsTotal(int d)
{
    m_discsTotal = d;
}

Job::DiscType Job::discType()
{
    return m_discType;
}

void Job::setDiscType(Job::DiscType type)
{
    m_discType = type;
}

void Job::setFiles(FileList files)
{
    m_files = files;
}

FileList Job::files()
{
    return m_files;
}

QString Job::name()
{
    return m_name;
}

void Job::setName(QString name)
{
    m_name = name;
}

QString Job::status()
{
    return m_status;
}

void Job::setStatus(QString status)
{
    m_status = status;
}

int Job::progress()
{
    return m_progress;
}

void Job::setProgress(int progress)
{
    m_progress = progress;
}
