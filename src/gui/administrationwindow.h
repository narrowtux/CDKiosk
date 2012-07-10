#ifndef ADMINISTRATIONWINDOW_H
#define ADMINISTRATIONWINDOW_H

#include <QWidget>
#include <QSettings>
#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class AdministrationWindow;
}

class AdministrationWindow : public QDialog
{
    Q_OBJECT
    
public:
    explicit AdministrationWindow(MainWindow *parent = 0);
    ~AdministrationWindow();
    
private slots:
    void on_checkShowAdminButton_toggled (bool checked);
    
    void on_linePassword_editingFinished();
    
    void on_checkPassword_toggled(bool checked);
    
	void on_buttonAddEntry_clicked();
	
	void on_buttonDeeleteEntry_clicked();
	
	void on_buttonEditEntry_clicked();
	
private:
    Ui::AdministrationWindow *ui;
    QSettings settings;
    MainWindow *m_parent;
};

#endif // ADMINISTRATIONWINDOW_H
