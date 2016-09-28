#include "ListenTick.h"

#include "utils.h"
#include "utils.c"

ListenTick::ListenTick(QObject *parent, const char *ip, int port) : QThread(parent),m_bIsRun(false)
{
    m_socket=NULL;
    m_bIsOpen=false;

    host=ip;
    m_iPort=port;

}

ListenTick::~ListenTick()
{
    //qDebug()<<"mq close";

}

void ListenTick::setAddress(QString sIp, QString sPort)
{
    m_sIp=sIp;

      qDebug()<<"set Ip "<<m_sIp;

    m_iPort=sPort.toInt();
}

int ListenTick::open()
{
    if(m_bIsOpen)
        return 0;

  //  const char *hostname=m_sIp.toStdString().c_str();

   //const char  *hostname="210.242.246.140";
  // int port=9999;

    const char  *hostname=host;
    int port=m_iPort;
    qDebug()<<"listen ip "<<m_sIp;

    int status;

    m_conn = amqp_new_connection();

    m_socket = amqp_tcp_socket_new(m_conn);
    if (!m_socket)
    {
        die("creating TCP socket");
    }

    status = amqp_socket_open(m_socket, hostname, port);
    if (status)
    {
        //die("opening TCP socket");
        qDebug()<<"open TCP socket";
    }

//    die_on_amqp_error(amqp_login(m_conn, "tw", 0, 16384, 60, AMQP_SASL_METHOD_PLAIN,
//                                 "user1", "user1.stock"),
//                      "Logging in");

    amqp_login(m_conn, "tw", 0, 16384, 60, AMQP_SASL_METHOD_PLAIN,
                                     "user1", "user1.stock");
    amqp_channel_open(m_conn, 1);
    die_on_amqp_error(amqp_get_rpc_reply(m_conn), "Opening channel");

   //{
        amqp_queue_declare_ok_t *r = amqp_queue_declare(m_conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
                                                        amqp_empty_table);
        die_on_amqp_error(amqp_get_rpc_reply(m_conn), "Declaring queue");
        m_queuename = amqp_bytes_malloc_dup(r->queue);
        if (m_queuename.bytes == NULL)
        {
            fprintf(stderr, "Out of memory while copying queue name");
            return 1;
        }
  //  }
    qDebug()<<"mq open: ";
    m_bIsOpen=true;
    return 0;
}

int ListenTick::setBindingKey(QString sType, QStringList argv, int iLoopMSec)
{

    if(!m_bIsOpen)
        open();

    m_bIsRun=false;
    char const *exchange="stock";


    exchange=sType.toStdString().c_str();
    m_iLoopMSec=iLoopMSec;

    int iRe=0;

    {

          QString tmp=QString(argv.at(0)).split(".").at(0)+".*";
          char const *tmp2=tmp.toStdString().c_str();
         // char const *tmp3=QString(argv.at(0)).toStdString().c_str();

         char const *bindingkey =tmp2;

        amqp_queue_bind(m_conn, 1, m_queuename, amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkey),
                        amqp_empty_table);

        m_currentBindingKey=bindingkey;
        die_on_amqp_error(amqp_get_rpc_reply(m_conn), "Binding queue");

    }


    amqp_basic_consume(m_conn, 1, m_queuename, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);


  //  die_on_amqp_error(amqp_get_rpc_reply(m_conn), "Consuming");

    m_bIsRun=true;
    return iRe;
}



void ListenTick::loopListen()
{

    amqp_rpc_reply_t res;
    amqp_envelope_t envelope;

    amqp_maybe_release_buffers(m_conn);

    res = amqp_consume_message(m_conn, &envelope, NULL, 0);

    if (AMQP_RESPONSE_NORMAL != res.reply_type)
    {
        //break;
        return;
    }

    /* ------------------------------------------------------------------ */
    /* 請將主要處理程式碼放在這個區塊, 以下只是範例, 將收到資料列印出來 */

    /* *-/
      printf("Delivery %u, exchange %.*s routingkey %.*s\n",
             (unsigned) envelope.delivery_tag,
             (int) envelope.exchange.len, (char *) envelope.exchange.bytes,
             (int) envelope.routing_key.len, (char *) envelope.routing_key.bytes);

      if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
        printf("Content-type: %.*s\n",
               (int) envelope.message.properties.content_type.len,
               (char *) envelope.message.properties.content_type.bytes);
      }
      printf("----\n");

      amqp_dump(envelope.message.body.bytes, envelope.message.body.len);
//--*/

    //      printf("%.*s\n", (int)envelope.message.body.len, (char *)envelope.message.body.bytes);
    //      fflush(stdout);
    QString st((char *)envelope.message.body.bytes);
    emit signalTick(st);


    /* *-/
      if ((unsigned) envelope.delivery_tag % 1000 == 0) {
        fprintf(stderr, "Got %u messages\n", envelope.delivery_tag);
      }
//--*/

    /* ------------------------------------------------------------------ */

    amqp_destroy_envelope(&envelope);

}

void ListenTick::close()
{
    if(!m_bIsOpen)
        return;

    m_bIsRun=false;

    qDebug()<<"mq close";
    die_on_amqp_error(amqp_channel_close(m_conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
    die_on_amqp_error(amqp_connection_close(m_conn, AMQP_REPLY_SUCCESS), "Closing connection");
    die_on_error(amqp_destroy_connection(m_conn), "Ending connection");
    msleep(1000);

}

//int ListenTick::startListen(char const *exchange,QStringList argv)
//{


//    char const *hostname="60.251.126.94";
//    int port=5672;
//    int status;

//    amqp_socket_t *socket = NULL;
//    amqp_connection_state_t conn;

//    amqp_bytes_t queuename;

//    if (4+argv.length() < 5) {
//        fprintf(stderr, "Usage: amqp_listen host port exchange bindingkey\n");
//        return 1;
//    }

//    //     hostname = m_argv[1];
//    //     port = atoi(m_argv[2]);
//    // exchange = m_argv[3];

//    conn = amqp_new_connection();

//    socket = amqp_tcp_socket_new(conn);
//    if (!socket)
//    {
//        die("creating TCP socket");
//    }

//    status = amqp_socket_open(socket, hostname, port);
//    if (status)
//    {
//        die("opening TCP socket");
//    }

//    die_on_amqp_error(amqp_login(conn, "tw", 0, 16384, 60, AMQP_SASL_METHOD_PLAIN,
//                                 "user1", "user1.stock"),
//                      "Logging in");
//    amqp_channel_open(conn, 1);
//    die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");

//    {
//        amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_empty_bytes, 0, 0, 0, 1,
//                                                        amqp_empty_table);
//        die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
//        queuename = amqp_bytes_malloc_dup(r->queue);
//        if (queuename.bytes == NULL)
//        {
//            fprintf(stderr, "Out of memory while copying queue name");
//            return 1;
//        }
//    }


//    {
//        int i;
//        for (i = 0; i < argv.length(); i++)
//        {
//            const char  *bindingkey = QString(argv.at(i)).toStdString().c_str();
//            amqp_queue_bind(conn, 1, queuename, amqp_cstring_bytes(exchange), amqp_cstring_bytes(bindingkey),
//                            amqp_empty_table);
//            die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
//        }
//    }

//    amqp_basic_consume(conn, 1, queuename, amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
//    die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");

//    {
//        //       for(;;)
//        //       {
//        //         amqp_rpc_reply_t res;
//        //         amqp_envelope_t envelope;

//        //         amqp_maybe_release_buffers(conn);

//        //         res = amqp_consume_message(conn, &envelope, NULL, 0);

//        //         if (AMQP_RESPONSE_NORMAL != res.reply_type)
//        //         {
//        //           break;
//        //         }


//        struct timeval timeout;     /* <sys/time.h> */
//        timeout.tv_sec = 0;
//        timeout.tv_usec = 1000;     /* 1/1000 seconds */

//        while (1)
//        {      /* global or shared variable */
//            amqp_rpc_reply_t res;
//            amqp_envelope_t envelope;
//            amqp_maybe_release_buffers(conn);

//            res = amqp_consume_message(conn, &envelope, &timeout, 0);
//            if (AMQP_RESPONSE_NORMAL != res.reply_type) {
//                if (AMQP_STATUS_TIMEOUT == res.library_error) {
//                    continue;             /* no message */
//                }
//                break;
//            }



//            /* ------------------------------------------------------------------ */
//            /* 請將主要處理程式碼放在這個區塊, 以下只是範例, 將收到資料列印出來 */

//            /* *-/
//         printf("Delivery %u, exchange %.*s routingkey %.*s\n",
//                (unsigned) envelope.delivery_tag,
//                (int) envelope.exchange.len, (char *) envelope.exchange.bytes,
//                (int) envelope.routing_key.len, (char *) envelope.routing_key.bytes);

//         if (envelope.message.properties._flags & AMQP_BASIC_CONTENT_TYPE_FLAG) {
//           printf("Content-type: %.*s\n",
//                  (int) envelope.message.properties.content_type.len,
//                  (char *) envelope.message.properties.content_type.bytes);
//         }
//         printf("----\n");

//         amqp_dump(envelope.message.body.bytes, envelope.message.body.len);
//   //--*/

//            printf("%.*s\n", (int)envelope.message.body.len, (char *)envelope.message.body.bytes);
//            fflush(stdout);

//            QString st((char *)envelope.message.body.bytes);
//            emit signalTick(st);

//            /* *-/
//         if ((unsigned) envelope.delivery_tag % 1000 == 0) {
//           fprintf(stderr, "Got %u messages\n", envelope.delivery_tag);
//         }
//   //--*/

//            /* ------------------------------------------------------------------ */

//            amqp_destroy_envelope(&envelope);


//        }
//    }

//    die_on_amqp_error(amqp_channel_close(conn, 1, AMQP_REPLY_SUCCESS), "Closing channel");
//    die_on_amqp_error(amqp_connection_close(conn, AMQP_REPLY_SUCCESS), "Closing connection");
//    die_on_error(amqp_destroy_connection(conn), "Ending connection");

//    return 0;
//}

void ListenTick::run()
{
    while(m_bIsRun)
    {

            loopListen();

            msleep(m_iLoopMSec);

    }

}



