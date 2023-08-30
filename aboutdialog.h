#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class AboutDialog;
}

class AboutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private slots:
    void on_label_Website_linkActivated(const QString &link);

private:
    Ui::AboutDialog *ui;
};

#endif // ABOUTDIALOG_H
