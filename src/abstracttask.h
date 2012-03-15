#ifndef ABSTRACTTASK_H
#define ABSTRACTTASK_H

#include <QObject>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "speech.h"

class BurnTask : public QObject
{
    Q_OBJECT
public:
    explicit BurnTask(QObject *parent = 0);
    
    QList<Speech*> speeches();
    bool isMP3();
    int copies();
signals:

public slots:

};

#endif // ABSTRACTTASK_H
