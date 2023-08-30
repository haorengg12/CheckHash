#include "workthread.h"

WorkThread::WorkThread(QObject *parent) : QThread (parent)
{
    m_CheckClass = new CheckClass();
    m_CheckClass->moveToThread(this);
}

void WorkThread::run()
{
    while (!m_Stop) {
        if(!m_Pause)
        {
            emit isCheckStart();
            QString m_CheckResult = m_CheckClass->checkHash(m_Path, m_Index);
            m_Pause = true;
            emit isCheckFinished(m_CheckResult);
        }
        if(!m_VerifyPause)
        {
            emit isCheckStart();
            bool m_VerifyResult = m_CheckClass->verifyHash(m_Key, m_VerifyKey);
            m_VerifyPause = true;
            emit isVerifyFinished(m_VerifyResult);
        }
        msleep(500);
    }
    quit();
}

void WorkThread::stopThread()
{
    m_Stop = true;
}

void WorkThread::setCheckParams(QString param1, QCryptographicHash::Algorithm param2)
{
    m_Path = param1;
    m_Index = param2;
    m_Pause = false;
}

void WorkThread::setVerifyParams(QString key, QString verifyKey)
{
    m_Key = key;
    m_VerifyKey = verifyKey;
    m_VerifyPause = false;
}
