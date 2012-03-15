#include "jobmanager.h"
#include <QApplication>

JobManager::JobManager(QDir workingDirectory, QObject *parent) :
    QObject(parent)
{
    m_workingDirectory = workingDirectory;
}

QDir JobManager::workingDirectory()
{
    return m_workingDirectory;
}
