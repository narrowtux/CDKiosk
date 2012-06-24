#ifndef PAINTUTILS_H
#define PAINTUTILS_H

#include <QObject>
#include <QtGui>
#include "src/speech/speech.h"
#include "src/jobmanager/job.h"

class PaintUtils : public QObject
{
    Q_OBJECT
public:
    explicit PaintUtils(QObject *parent = 0);
    static void drawRoundedText(QPainter *painter, int x, int y, QString text, int radius);
    static QPixmap generateCoverForJob(QList<Speech*> speeches, Job::DiscType);
    static void setFontSize(QPainter *p, qreal size);
signals:
    
public slots:
    
};

#endif // PAINTUTILS_H
