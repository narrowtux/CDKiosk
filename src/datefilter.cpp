#include "datefilter.h"

DateFilter::DateFilter(QListWidget *listWidget)
{
    this->list = listWidget;
}

bool DateFilter::matches(Speech *object)
{
    if(list->currentRow() == 0) {
	return true;
    } else {
	return list->currentItem()->text()==getDateString(object->date());
    }
}

QString DateFilter::getDateString(QDate date)
{
    return date.toString("MMM yyyy");
}
