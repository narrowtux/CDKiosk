#ifndef AUTHORFILTER_H
#define AUTHORFILTER_H

#include <QListWidget>
#include "src/filter/filter.h"
#include "src/speech/speech.h"

class AuthorFilter : public Filter
{
private:
    QListWidget *list;
public:
    AuthorFilter(QListWidget *listWidget);
    bool matches(Speech *speech);
};

#endif // AUTHORFILTER_H
