#ifndef WORKTHREAD_H
#define WORKTHREAD_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "checkclass.h"

class WorkThread : public QThread
{
    Q_OBJECT
public:
    WorkThread(QObject *parent = nullptr);

    void run();

    void stopThread();

    void setCheckParams(QString param1, QCryptographicHash::Algorithm param2);

    void setVerifyParams(QString key, QString verifyKey);

public:
    CheckClass *m_CheckClass = nullptr;

signals:
    void isCheckStart();
    void isCheckFinished(QString param);
    void isVerifyFinished(bool param);

private:
    int kk = 0;
    QString m_Path = "";
    QString m_Key = "";
    QString m_VerifyKey = "";
    bool m_Stop = false;
    bool m_Pause = true;
    bool m_VerifyPause = true;
    QCryptographicHash::Algorithm m_Index;

};

#endif // WORKTHREAD_H
