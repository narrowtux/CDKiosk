#include "speechmodel.h"

int SpeechModel::ROLE_ITEM_LEVEL = Qt::UserRole + 1032;
int SpeechModel::ROLE_SPEECH_PROPERTY = Qt::UserRole + 1033;

SpeechModel::SpeechModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

QModelIndex SpeechModel::index(int row, int column, const QModelIndex &parent) const
{
    if(parent.data(ROLE_ITEM_LEVEL).toInt() == 1) {
	//This would be an actual speech.
	Speech *speech;
	if(row < m_speeches.size()) {
	    speech = m_speeches.values().at(row);
	    QModelIndex index = createIndex(row, column, speech);
	} else {
	    return QModelIndex();
	}
    }
}

QModelIndex SpeechModel::parent(const QModelIndex &child) const
{
    
}

int SpeechModel::rowCount(const QModelIndex &parent) const
{
    
}

void SpeechModel::updateReferents()
{
    beginResetModel();
    m_referents.clear();
    foreach(Speech *speech, m_speeches.values()) {
	if(!m_referents.contains(speech->author())) {
	    m_referents.append(speech->author());
	}
    }
    qSort(m_referents);
    endResetModel();
}

void SpeechModel::addSpeech(Speech *speech)
{
    m_speeches.insert(speech->databaseId(), speech);
    updateReferents();
}

int SpeechModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant SpeechModel::data(const QModelIndex &index, int role) const
{
    
}
