#ifndef GROUPFILTER_H
#define GROUPFILTER_H

#include <QListWidget>
#include "filter.h"
#include "speech.h"

class GroupFilter : public Filter
{
private:
    QListWidget *list;
public:
    GroupFilter(QListWidget *listWidget);
    bool matches(Speech *object);
};

#endif // GROUPFILTER_H
