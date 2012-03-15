#ifndef JOB_H
#define JOB_H

#include <QObject>
#include <QtCore>
#include "cover.h"

typedef QList<QString> FileList;

class Job : public QObject
{
    Q_OBJECT
public:
    enum DiscType {
	FILES,
	AUDIO
    };

    explicit Job(QObject *parent = 0);
    int discsDone();
    int discsTotal();
    void setDiscsDone(int d);
    void setDiscsTotal(int d);
    DiscType discType();
    void setDiscType(DiscType type);
    void setFiles(FileList files);
    FileList files();
    QString name();
    void setName(QString name);
    QString status();
    void setStatus(QString status);
    int progress();
    void setProgress(int progress);
signals:
    
public slots:
private:
    int m_discsDone, m_discsTotal;
    DiscType m_discType;
    FileList m_files;
    Cover *m_cover;
    QString m_name;
    QString m_status;
    int m_progress;
};

#endif // JOB_H
