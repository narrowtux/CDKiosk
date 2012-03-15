#ifndef ADMINISTRATIONWINDOW_H
#define ADMINISTRATIONWINDOW_H

#include <QWidget>
#include <QSettings>
#include "mainwindow.h"

namespace Ui {
class AdministrationWindow;
}

class AdministrationWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit AdministrationWindow(MainWindow *parent = 0);
    ~AdministrationWindow();
    
private slots:
    void on_checkShowAdminButton_toggled (bool checked);
    
    void on_linePassword_editingFinished();
    
    void on_checkPassword_toggled(bool checked);
    
private:
    Ui::AdministrationWindow *ui;
    QSettings settings;
    MainWindow *m_parent;
};

#endif // ADMINISTRATIONWINDOW_H
