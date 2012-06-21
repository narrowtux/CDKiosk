#ifndef SPEECHMANAGER_H
#define SPEECHMANAGER_H

#include <QObject>
#include "src/speech/speech.h"
#include "src/filter/filter.h"
#include <QMap>

class SpeechManager : public QObject
{
    Q_OBJECT
public:
    explicit SpeechManager(QObject *parent = 0);
    QList<QString> getDates();
    QList<QString> getAuthors();
    QList<QString> getGroups();
    QList<Speech*> speeches();
    void addSpeech(Speech *speech);
    Speech *speech(int databaseId);

    QList<Speech*> getFilteredSpeeches();
    void addFilter(Filter *filter);
    void load();
    void save();
private:
    QMap<int, Speech *> m_speeches;
    QList<QString> m_groupsCache;
    bool groupsDirty;
    QList<QString> m_authorsCache;
    bool authorsDirty;
    QList<QString> m_datesCache;
    bool datesDirty;

    QList<Filter*> m_filters;
private slots:
    void dirtyAll();
signals:

public slots:

};

#endif // SPEECHMANAGER_H
