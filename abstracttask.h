#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class AbstractTask : public QObject
{
    Q_OBJECT
public:
    explicit AbstractTask(QObject *parent = 0);
    QTreeWidgetItem *getItem(QTreeWidget *forWidget);
    
    //TODO: handle burn to disk
signals:

public slots:

};

#endif // ABSTRACTTASK_H
