#ifndef SPEECHMODEL_H
#define SPEECHMODEL_H

#include <QAbstractItemModel>
#include <QMap>
#include "speech.h"

class SpeechModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SpeechModel(QObject *parent = 0);
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const ;
    QVariant data(const QModelIndex &index, int role) const;
    
    void addSpeech(Speech *speech);
signals:

public slots:
private:
    void updateReferents();
    QMap<int, Speech *> m_speeches;
    QList<QString> m_referents;
    static int ROLE_ITEM_LEVEL;
    static int ROLE_SPEECH_PROPERTY;
};

#endif // SPEECHMODEL_H
