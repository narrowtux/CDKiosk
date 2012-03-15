#ifndef FILTER_H
#define FILTER_H

#include "speech.h"

class Filter
{
public:
    virtual bool matches(Speech *object);
signals:

public slots:

};

#endif // FILTER_H
