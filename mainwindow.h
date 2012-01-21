#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "speechmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
	static const int ROLE_DATABASE_ID;
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    SpeechManager * speechManager();
public slots:
    void showChoosePage();
    void showCartPage();
    void showBurnPage();
    void cleanGui();
    void updateChooseLists();
    void updateSpeechList();

private slots:
    void on_toolAddAmount_clicked();
    void on_toolRemoveAmount_clicked();

private:
    Ui::MainWindow *ui;

    int amount();
    void setAmount(int a);

    int m_amount;

    SpeechManager m_speechManager;
};

#endif // MAINWINDOW_H
