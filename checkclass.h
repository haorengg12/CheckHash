#ifndef CHECKCLASS_H
#define CHECKCLASS_H

#include <QObject>
#include <QFile>
#include <QCryptographicHash>
#include <QDebug>
#include <QByteArray>
#include <QMessageBox>
#include <QFileDialog>
#include <windows.h>
#include <QString>

class CheckClass : public QObject
{
    Q_OBJECT
public:
    explicit CheckClass(QObject *parent = nullptr);

    QString checkHash(QString srcDir, QCryptographicHash::Algorithm index);

    bool verifyHash(QString param1, QString param2);

};

#endif // CHECKCLASS_H
