#ifndef WAITDIALOG_H
#define WAITDIALOG_H

#include <QDialog>

namespace Ui {
class WaitDialog;
}

class WaitDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WaitDialog(QWidget *parent = nullptr);
    ~WaitDialog();

protected:
    void changeEvent(QEvent *event);

private:
    Ui::WaitDialog *ui;
};

#endif // WAITDIALOG_H
