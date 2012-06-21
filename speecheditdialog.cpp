#include "speecheditdialog.h"
#include "ui_speecheditdialog.h"

SpeechEditDialog::SpeechEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpeechEditDialog)
{
    ui->setupUi(this);
}

SpeechEditDialog::~SpeechEditDialog()
{
    delete ui;
}
