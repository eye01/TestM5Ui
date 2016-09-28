#include "TestTick.h"

TestTick::TestTick(QObject *parent, const char *ip, int port) : ListenTick(parent,ip,port)
{
    m_iLoopMSec=1000;
    QObject::startTimer(1000);
}

int TestTick::setBindingKey(QString sType, QStringList argv, int iLoopMSec)
{
    m_bIsRun=true;
    m_iLoopMSec=iLoopMSec;


    QStringList list=QString(argv.at(0)).split(".");

    if(list.length()>1)
        m_sNums=list.at(1);

    QString sFile=QString("../rabbitMq/data/%1_%2").arg(sType).arg(list.at(0));
    qDebug()<<"test tick file : "<<sFile;
    loadFile(sFile);
    return 0;
}



void TestTick::loopListen()
{

        if(m_iIdx!=-1)
        {
            if(m_iIdx>=m_listData.length())
                m_iIdx=0;

            if(m_listData.length()>1)
            {
                QStringList listCurrentData=QString(m_listData.at(m_iIdx)).split(" ");
                if(m_sNums=="*")
                {
                    emit signalTick(m_listData.at(m_iIdx));
                }
                else if(listCurrentData.length()>1 && listCurrentData.at(0) == m_sNums)
                {
                  //  qDebug()<<" select  id ="<<m_sNums<<"is: "<<m_listData.at(m_iIdx);
                    emit signalTick(m_listData.at(m_iIdx));
                }
                m_iIdx++;
            }
        }

}

void TestTick::loadFile(QString sFile)
{
    m_iIdx=-1;
    QFile file(sFile);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    m_listData.clear();
    QTextStream in(&file);

    int iLine=0;
    while (!in.atEnd())
    {

        m_listData.append(in.readLine());
        iLine++;
    }

    m_iIdx=0;
}

void TestTick::run()
{
    while(m_bIsRun)
    {

        loopListen();

        msleep(3000);

    }
}

