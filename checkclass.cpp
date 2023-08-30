#include "checkclass.h"

CheckClass::CheckClass(QObject *parent) : QObject(parent)
{

}

QString CheckClass::checkHash(QString srcDir, QCryptographicHash::Algorithm index)
{
    QString tempStr = "";
    QFile *file = new QFile(srcDir);
    QCryptographicHash *hash = new QCryptographicHash(index);
    if(file->open(QIODevice::ReadOnly))
    {
        hash->addData(file);
        tempStr = hash->result().toHex().data();
        file->close();
    }
    else
    {
        QMessageBox::warning(nullptr, "错误", "读取文件失败");
    }
    return tempStr;
}

bool CheckClass::verifyHash(QString param1, QString param2)
{
    if(param1 == param2)
    {
        return true;
    }
    else
    {
        return false;
    }
}
