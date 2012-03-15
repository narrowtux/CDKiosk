#include "administrationwindow.h"
#include "ui_administrationwindow.h"
#include <QKeySequence>

AdministrationWindow::AdministrationWindow(MainWindow *parent) :
    QWidget(0),
    ui(new Ui::AdministrationWindow)
{
    ui->setupUi(this);
    ui->checkShowAdminButton->setChecked(settings.value("showAdminButton", true).toBool());
    QString password = settings.value("password", "").toString();
    ui->checkPassword->setChecked(password != "");
    ui->linePassword->setText(password);
    
    QKeySequence seq = QKeySequence::Preferences;
    
    ui->labelShortcutHint->setText(tr("You can always show this window by pressing %0").arg(seq.toString(QKeySequence::NativeText)));
}

AdministrationWindow::~AdministrationWindow()
{
    delete ui;
}

void AdministrationWindow::on_checkShowAdminButton_toggled(bool checked)
{
    if(checked) {
	ui->labelShortcutHint->setStyleSheet("");
    } else {
	ui->labelShortcutHint->setStyleSheet("color:red");
    }
    settings.setValue("showAdminButton", checked);
}

void AdministrationWindow::on_linePassword_editingFinished()
{
    settings.setValue("password", ui->linePassword->text());
}

void AdministrationWindow::on_checkPassword_toggled(bool checked)
{
    if(!checked) {
	settings.setValue("password", "");
	ui->linePassword->setText("");
    } else {
	ui->linePassword->setFocus();
    }
}
