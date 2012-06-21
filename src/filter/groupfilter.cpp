#include "groupfilter.h"

GroupFilter::GroupFilter(QListWidget *listWidget)
{
    list = listWidget;
}

bool GroupFilter::matches(Speech *object)
{
    if(list->currentRow() == 0) {
	return true;
    }
    if(list->currentRow() == list->count() - 1) {
	return object->group() == "";
    }
    if(list->currentItem()) {
	return list->currentItem()->text() == object->group();
    }
    return false;
}
