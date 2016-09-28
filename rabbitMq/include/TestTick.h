#ifndef TESTTICK_H
#define TESTTICK_H

#include <QObject>
#include <QFile>

#include "ListenTick.h"
class TestTick : public ListenTick
{
    Q_OBJECT
public:
    explicit TestTick(QObject *parent , const char *ip="192.168.0.35", int port=5672);
    int setBindingKey(QString sType, QStringList argv, int iLoopMSec =3000);
    void close(){m_bIsRun=false;}
private:


    int open(){m_bIsOpen=true; return 0;}

    void loopListen();

    int m_iIdx;
    QString m_sNums;

    QStringList m_listData;
    void loadFile(QString sFile);
    void run();
signals:

public slots:
};

#endif // TESTTICK_H
