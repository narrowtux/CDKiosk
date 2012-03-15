#include "job.h"

Job::Job(QObject *parent) :
    QObject(parent)
{
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
