#ifndef SPEECH_H
#define SPEECH_H

#include <QObject>
#include <QDate>

class Speech : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString Name READ name WRITE setName)
    Q_PROPERTY(QString Author READ author WRITE setAuthor)
    Q_PROPERTY(QString FilenameMP3 READ filenameMP3 WRITE setFilenameMP3)
    Q_PROPERTY(QDate Date READ date WRITE setDate)
    Q_PROPERTY(int DatabaseId READ databaseId WRITE setDatabaseId)
    Q_PROPERTY(QString Group READ group WRITE setGroup)

public:
    Speech();
    
    QString compiledName();

    QString name() const
    {
	return m_Name;
    }

    QString author() const
    {
	return m_Author;
    }

    QString filenameMP3() const
    {
	return m_FilenameMP3;
    }
    
    QDate date() const
    {
	return m_Date;
    }

    int databaseId() const
    {
	return m_DatabaseId;
    }

    QString group() const
    {
	return m_Group;
    }

public slots:
    void setName(QString arg)
    {
	m_Name = arg;
    }

    void setAuthor(QString arg)
    {
	m_Author = arg;
    }

    void setFilenameMP3(QString arg)
    {
	m_FilenameMP3 = arg;
    }

    void setDate(QDate arg)
    {
	m_Date = arg;
    }

    void setDatabaseId(int arg)
    {
	m_DatabaseId = arg;
    }

    void setGroup(QString arg)
    {
	m_Group = arg;
    }

private:
    QString m_Name;

    QString m_Author;

    QString m_FilenameMP3;

    QDate m_Date;

    int m_DatabaseId;

    QString m_Group;
    
    static int nextDatabaseId;
};

#endif // SPEECH_H
