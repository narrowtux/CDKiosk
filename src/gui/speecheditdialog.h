#ifndef SPEECHEDITDIALOG_H
#define SPEECHEDITDIALOG_H

#include <QDialog>

namespace Ui {
class SpeechEditDialog;
}

class SpeechEditDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit SpeechEditDialog(QWidget *parent = 0);
    ~SpeechEditDialog();
    
private:
    Ui::SpeechEditDialog *ui;
};

#endif // SPEECHEDITDIALOG_H
