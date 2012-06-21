#include "authorfilter.h"

AuthorFilter::AuthorFilter(QListWidget *listWidget)
{
    list = listWidget;
}

bool AuthorFilter::matches(Speech *speech) {
    if (list->currentRow() == 0) {
	return true;
    }
    if(list->currentItem()) {
	return speech->author() == list->currentItem()->text();
    }
    return false;
}
