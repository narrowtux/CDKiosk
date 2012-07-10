#ifndef DATABASEENTRYDIALOG_H
#define DATABASEENTRYDIALOG_H

#include <QDialog>
#include <QFileDialog>

namespace Ui {
class DatabaseEntryDialog;
}

class DatabaseEntryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DatabaseEntryDialog(int id, QWidget *parent = 0);
    ~DatabaseEntryDialog();
    
public slots:
    void onFileDialogClosed();
    
private slots:
    void on_buttonSelectFile_clicked();
    
	void on_buttonToday_clicked();
	
	void on_buttonBox_accepted();
	
private:
    Ui::DatabaseEntryDialog *ui;
    int m_databaseId;
    QString m_fileLocation;
    QFileDialog *m_currentFileDialog;
	void updateFileButton();
};

#endif // DATABASEENTRYDIALOG_H
