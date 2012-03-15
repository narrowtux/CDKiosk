#include "jobmanagermac.h"

JobManagerMac::JobManagerMac(QDir workingDirectory, QObject *parent) : JobManager(workingDirectory, parent)
{
    qDebug()<<"Initializing PT Job Manager";
    char *appName = const_cast<char*>(qApp->applicationName().toStdString().c_str());
    char *workDir = const_cast<char*>(this->workingDirectory().absolutePath().toStdString().c_str());
    char *appVersion = const_cast<char*>(qApp->applicationVersion().toStdString().c_str());
    m_jobManagerId = JM_Initialize(workDir, appName, appVersion, false);
}
