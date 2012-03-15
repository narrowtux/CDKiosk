#ifndef DATEFILTER_H
#define DATEFILTER_H

#include "filter.h"
#include <QListWidget>

class DateFilter : public Filter
{
private:
    QListWidget *list;
public:
    DateFilter(QListWidget *listWidget);
    bool matches(Speech* object);
    static QString getDateString(QDate date);
};

#endif // DATEFILTER_H
