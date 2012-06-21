#ifndef GROUPFILTER_H
#define GROUPFILTER_H

#include <QListWidget>
#include "src/filter/filter.h"
#include "src/speech/speech.h"

class GroupFilter : public Filter
{
private:
    QListWidget *list;
public:
    GroupFilter(QListWidget *listWidget);
    bool matches(Speech *object);
};

#endif // GROUPFILTER_H
