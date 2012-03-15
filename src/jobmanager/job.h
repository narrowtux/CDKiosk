#ifndef JOB_H
#define JOB_H

#include <QObject>

class Job : public QObject
{
    Q_OBJECT
public:
    explicit Job(QObject *parent = 0);
    int discsDone();
    int discsTotal();
    void setDiscsDone(int d);
    void setDiscsTotal(int d);
signals:
    
public slots:
private:
    int m_discsDone, m_discsTotal;
    
};

#endif // JOB_H
