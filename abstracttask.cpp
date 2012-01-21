#include "abstracttask.h"

AbstractTask::AbstractTask(QObject *parent) :
    QObject(parent)
{
}

QTreeWidgetItem * AbstractTask::getItem(QTreeWidget *forWidget)
{
}
