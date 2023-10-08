#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowTitle("关于此软件");
    QPixmap pic(":/mainwindow/icon/Res/ProfilePicture.jpg");
    ui->label_my_photo->setPixmap(pic.scaled(ui->label_my_photo->width(), ui->label_my_photo->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    setModal(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::closeEvent(QCloseEvent *event)
{
    ui->label_Website->setText(QApplication::translate("AboutDialog", "<html><head/><body><p><a href=\"https://github.com/haorengg12\"><span style=\" text-decoration: underline; color:#0066cc;\">Harley·Huang</span></a></p></body></html>", Q_NULLPTR));
}

void AboutDialog::changeEvent(QEvent *event)
{
    QDialog::changeEvent(event);
    switch (event->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void AboutDialog::on_label_Website_linkActivated(const QString &link)
{
    ui->label_Website->setText(QApplication::translate("AboutDialog", "<html><head/><body><p><a href=\"https://github.com/haorengg12/CheckHash\"><span style=\" text-decoration: underline; color:#800080;\">Harley·Huang</span></a></p></body></html>", Q_NULLPTR));
    QUrl url(link);
    QDesktopServices::openUrl(url);
}
