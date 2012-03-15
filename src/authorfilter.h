#ifndef AUTHORFILTER_H
#define AUTHORFILTER_H

#include <QListWidget>
#include "speech.h"
#include "filter.h"

class AuthorFilter : public Filter
{
private:
    QListWidget *list;
public:
    AuthorFilter(QListWidget *listWidget);
    bool matches(Speech *speech);
};

#endif // AUTHORFILTER_H
