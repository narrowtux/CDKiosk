#ifndef JOBMANAGERMAC_H
#define JOBMANAGERMAC_H
#include "../jobmanager.h"
#include <QtCore>

class JobManagerMac : public JobManager
{
public:
    JobManagerMac(QDir workingDirectory, QObject *parent);
private:
    UInt32 m_jobManagerId;
};

#endif // JOBMANAGERMAC_H
