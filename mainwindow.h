#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <windows.h>
#include "workthread.h"
#include <QCloseEvent>
#include "waitdialog.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void onKeyChecked(QCryptographicHash::Algorithm index);

public slots:
    void onCheckStart();
    void onCheckFinished(QString param);
    void onVerifyFinished(bool param);

private slots:
    void on_pushButton_SelectFile_clicked();

    void on_pushButton_Verify_clicked();

    void on_pushButton_Exit_clicked();

    void on_comboBox_SelectCoder_currentIndexChanged(int index);

    void on_action_About_triggered();

protected:
    void closeEvent(QCloseEvent *event);
    void changeEvent(QEvent *event);

private:
    Ui::MainWindow *ui;
    WaitDialog *m_WaitDialog = nullptr;
    AboutDialog *m_AboutDialog = nullptr;

    WorkThread *m_WorkThread = nullptr;

    QString filePath = "";
};

#endif // MAINWINDOW_H
