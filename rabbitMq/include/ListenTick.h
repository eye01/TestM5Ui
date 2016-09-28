#ifndef LISTENTICK_H
#define LISTENTICK_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <QString>
#include <QStringList>

#include <string.h>

#include <stdint.h>
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

#include <assert.h>


#define STOCK "stock"

#define TAIFEX "taifex"


class ListenTick : public QThread
{
    Q_OBJECT
public:
    explicit ListenTick(QObject *parent,const char * ip,int port);

    ~ListenTick();


    /**
     * @brief setBindingKey
     * @param MQ_TYPE _stock  or  _taifex
     * @param argv      stock:  "tse.*" "otc.*" "emg.*"
     *                              taifex:  "tfe.*" "opt.*"                         * =all  , or keyin number
     * @param iLoopMSec loop delay millisecond
     * @return
     */



    /**
     * @brief startListen  保留原範例
     * @param exchange
     * @param argv
     * @return
     */
  //  int startListen(char const *exchange,QStringList argv);

    void setAddress(QString sIp,QString sPort);

    int setBindingKey(QString sType, QStringList argv, int iLoopMSec=500);

    int resetBindingKey(QString sType, QStringList argv, int iLoopMSec=500);

    void close();
     bool m_bIsRun;

     QString m_sIp;

     int m_iPort;

     const char *host;
protected:

    bool m_bIsOpen;

     char const *m_currentBindingKey;

    int m_iLoopMSec;

    amqp_socket_t *m_socket;

    amqp_connection_state_t m_conn;

    amqp_bytes_t m_queuename;


    int i;
    int open();

    void loopListen();

    void run();

signals:

    void signalTick(QString st);

public slots:
};

#endif // LISTENTICK_H
