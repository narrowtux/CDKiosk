#ifndef SPEECHMODEL_H
#define SPEECHMODEL_H

#include <QAbstractItemModel>

class SpeechModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit SpeechModel(QObject *parent = 0);

signals:

public slots:

};

#endif // SPEECHMODEL_H
