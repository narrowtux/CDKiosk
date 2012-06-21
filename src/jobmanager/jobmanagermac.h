#ifndef JOBMANAGERMAC_H
#define JOBMANAGERMAC_H

#ifdef USE_MAC_JOBMANAGER
#include "../jobmanager.h"
#include <QtCore>

class JobManagerMac : public JobManager
{
public:
    JobManagerMac(QDir workingDirectory, QObject *parent);
private:
    UInt32 m_jobManagerId;
};

#endif

#endif // JOBMANAGERMAC_H
