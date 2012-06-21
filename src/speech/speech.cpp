#include "speech.h"

int Speech::nextDatabaseId = 0;

Speech::Speech() :
    QObject(0)
{
    m_DatabaseId = nextDatabaseId++;
}

QString Speech::compiledName()
{
    QString dateStr = date().toString(Qt::SystemLocaleDate);
    if(name().isEmpty()) {
	return tr("Speech at %0 by %1").arg(dateStr).arg(author());
    } else {
	return tr("%0 at %1 by %2").arg(name()).arg(dateStr).arg(author());
    }
}
