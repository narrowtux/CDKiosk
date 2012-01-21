#include "speechmanager.h"
#include "datefilter.h"

SpeechManager::SpeechManager(QObject *parent) :
    QObject(parent)
{
    dirtyAll();
}

QList<QString> SpeechManager::getDates()
{
    if(!datesDirty) {
	return m_datesCache;
    }
    QList<QString> ret;
    foreach(Speech* speech, m_speeches) {
	QString date = DateFilter::getDateString(speech->date());
	if(!ret.contains(date)) {
	    ret.append(date);
	}
    }
    m_datesCache = ret;
    datesDirty = false;
    return ret;
}

QList<QString> SpeechManager::getAuthors()
{
    if(!groupsDirty) {
	return m_authorsCache;
    }
    QList<QString> ret;
    foreach(Speech* speech, m_speeches) {
	QString author = speech->author();
	if(author == 0 || author == "") {
	    author = tr("None");
	}
	if(!ret.contains(author)) {
	    ret.append(author);
	}
    }
    m_authorsCache = ret;
    authorsDirty = false;
    return ret;
}

QList<QString> SpeechManager::getGroups()
{
    if(!groupsDirty) {
	return m_groupsCache;
    }
    QList<QString> ret;
    foreach(Speech* speech, m_speeches) {
	QString group = speech->group();
	if(group == 0 || group == "") {
	    continue;
	}
	if(!ret.contains(group)) {
	    ret.append(group);
	}
    }
    m_groupsCache = ret;
    groupsDirty = false;
    return ret;
}

QList<Speech *> SpeechManager::speeches()
{
    return m_speeches;
}

void SpeechManager::load()
{
}

void SpeechManager::save()
{
}

void SpeechManager::dirtyAll()
{
    groupsDirty = true;
    authorsDirty = true;
    datesDirty = true;
}

void SpeechManager::addFilter(Filter *filter)
{
    m_filters << filter;
}

QList<Speech *> SpeechManager::getFilteredSpeeches()
{
    QList<Speech *> ret;
    foreach(Speech * speech, m_speeches) {
	bool matches = true;
	foreach(Filter *filter, m_filters) {
	    if(!filter->matches(speech)) {
		matches = false;
		break;
	    }
	}
	if(matches) {
	    ret.append(speech);
	}
    }
    return ret;
}

void SpeechManager::addSpeech(Speech *speech)
{
    m_speeches << speech;
    dirtyAll();
}
