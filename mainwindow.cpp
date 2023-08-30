#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/mainwindow/icon/Res/Mainwindow.ico"));
    setWindowTitle("文件校验");

    m_WaitDialog = new WaitDialog(this);
    m_AboutDialog = new AboutDialog(this);
    m_WorkThread = new WorkThread(this);
    connect(m_WorkThread, SIGNAL(isCheckStart()), this, SLOT(onCheckStart()));
    connect(m_WorkThread, SIGNAL(isCheckFinished(QString)), this, SLOT(onCheckFinished(QString)));
    connect(m_WorkThread, SIGNAL(isVerifyFinished(bool)), this, SLOT(onVerifyFinished(bool)));
    m_WorkThread->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onKeyChecked(QCryptographicHash::Algorithm index)
{
    if(filePath != "")
    {
        ui->lineEdit_filePath->setText(filePath);
        switch (ui->comboBox_SelectCoder->currentIndex()) {
        case 0:
            index = QCryptographicHash::Md5;
            break;
        case 1:
            index = QCryptographicHash::Sha1;
            break;
        case 2:
            index = QCryptographicHash::Sha256;
            break;
        default:
            index = QCryptographicHash::Md5;
            break;
        }
        m_WorkThread->setCheckParams(filePath, index);
    }
    else
    {
        QMessageBox::warning(this, "警告", "忘记选择文件了呢~");
    }
}

void MainWindow::onCheckStart()
{
    m_WaitDialog->show();
}

void MainWindow::onCheckFinished(QString param)
{
    m_WaitDialog->close();
    ui->lineEdit_Key->setText(param);
}

void MainWindow::onVerifyFinished(bool param)
{
    m_WaitDialog->close();
    QMessageBox::information(this, "信息", param? "匹配呢~": "不匹配的啦~");
}

void MainWindow::on_pushButton_SelectFile_clicked()
{
//    SHA-256 Hash: 9a0b78e089600050673e6d6899b02ee9f2f9d4e4b87bd6c0d225a23e0fcd1fb9
//    SHA-1 Hash: 967298c18608d7da3863aca87641736cee3912a0
//    MD5 Hash: afa3092203831f9eaf52b07ccf4fd738
    QCryptographicHash::Algorithm index;
    ui->lineEdit_filePath->setText("");
    ui->lineEdit_Key->setText("");
    filePath = QFileDialog::getOpenFileName(this, tr("请选择校验文件。。。"), "D:\\", "*.*"
                                            , Q_NULLPTR, QFileDialog::DontUseNativeDialog);
    onKeyChecked(index);
}

void MainWindow::on_pushButton_Verify_clicked()
{
    QString keyStr = ui->lineEdit_Key->text();
    QString verifyKeyStr = ui->lineEdit_VerifyKey->text();
    int keyLength = keyStr.length();
    int verifyKeyLength = verifyKeyStr.length();
    if(!keyLength)
    {
        QMessageBox::warning(this, "警告", "空值怎么校验啊~");
    }
    else if(!verifyKeyLength)
    {
        QMessageBox::warning(this, "警告", "空值怎么校验啊~");
    }
    else if(keyLength != verifyKeyLength)
    {
        QMessageBox::warning(this, "警告", "长度不同呢~");
    }
    else
    {
        m_WorkThread->setVerifyParams(keyStr, verifyKeyStr);
    }
}

void MainWindow::on_pushButton_Exit_clicked()
{
    close();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_WorkThread->isRunning())
    {
        m_WorkThread->stopThread();
        m_WorkThread->wait();
    }
    event->accept();
}

void MainWindow::changeEvent(QEvent *event)
{
    QMainWindow::changeEvent(event);
    switch (event->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_comboBox_SelectCoder_currentIndexChanged(int index)
{
    if(!(ui->lineEdit_filePath->text() == ""))
    {
        onKeyChecked((QCryptographicHash::Algorithm)index);
    }
}

void MainWindow::on_action_About_triggered()
{
    m_AboutDialog->show();
}
