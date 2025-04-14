#include "ConsumerKafka.h"

#include <QLibrary>
#include <QDebug>
#include <QElapsedTimer>
#include <QCoreApplication>

bool g_bLoadedCppLib = false;

//typedef Conf *(*rd_conf_create_decl) (Conf::ConfType type);
ConsumerKafka::ConsumerKafka()
{

}

ConsumerKafka::~ConsumerKafka()
{

}

//bool ConsumerKafka::LoadCppLiberary(const QString& dllName)
//{
//    QLibrary lib(dllName);
//    if( !lib.load() )
//    {
//        //qDebug() << "Failed to load dll" + dllName;
//        qDebug() << QString("Failed to load dll") + dllName + "\n error:" + lib.errorString();
//        return false;
//    }
//    else
//    {
//        qDebug() << QString("Loading dll succeeded!") + dllName;
//        g_bLoadedCppLib = true;
//        //rd_conf_create_decl thtf_conf_create = (rd_conf_create_decl)lib.resolve("Conf::create");
//        //global_conf = thtf_conf_create(RdKafka::Conf::CONF_GLOBAL);
//        //global_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
//    }
//    return true;
//}


//int ConsumerKafka::InitKafka(int _partition, std::string broker, std::string _topic)
//{
//    if( !g_bLoadedCppLib )
//        return -1;
//    //global_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
//    //topic_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

//    return 0;
//}

int ConsumerKafka::init_kafka(int _partition, std::string broker, std::string _topic)
{
    global_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    topic_conf = RdKafka::Conf::create(RdKafka::Conf::CONF_TOPIC);

    brokers = broker;
    partition = _partition;
    topic_name = _topic;
    start_offset = RdKafka::Topic::OFFSET_BEGINNING;
    global_conf->set("metadata.broker.list", brokers, errstr);

    MyEventCb ex_event_cb;
    global_conf->set("event_cb", &ex_event_cb, errstr);

    /*
    * Create consumer using accumulated global configuration.
    */
    consumer = RdKafka::Consumer::create(global_conf, errstr);
    if (!consumer) {
        std::cerr << "Failed to create consumer: " << errstr << std::endl;
        exit(1);
    }
     /* Create topic */
    topic = RdKafka::Topic::create(consumer, topic_name, topic_conf, errstr);
    if (!topic) {
        std::cerr << "Failed to create topic: " << errstr << std::endl;
        exit(1);
    }
}

void ConsumerKafka::destroy()
{
    consumer->stop(topic, partition);
    consumer->poll(1000);

    delete topic;
    delete consumer;
}

int ConsumerKafka::pull_data_from_kafka()
{
    RdKafka::ErrorCode resp = consumer->start(topic, partition, start_offset);
    if (resp != RdKafka::ERR_NO_ERROR) {
        std::cerr << "Failed to start consumer: " << RdKafka::err2str(resp) << std::endl;
        exit(1);
    }

    /*
    * Consume messages
    */

    MyConsumeCb ex_consume_cb;
    int use_ccb = 0;

    m_bRun = true;
    QElapsedTimer t;
    t.start();
    //qDebug() << t.elapsed() << endl;
    while(m_bRun)
    {
        QCoreApplication::processEvents();
        if (use_ccb) {
            //consumer->consume_callback(topic, partition, 1000, &ex_consume_cb, &use_ccb);
        } else {
            RdKafka::Message *msg = consumer->consume(topic, partition, 1000);
            msg_consume(msg, NULL);
            delete msg;
        }
        consumer->poll(0);
    }
}

void ConsumerKafka::pull_data_stop()
{
    m_bRun = false;
}

void msg_consume(RdKafka::Message* message, void* opaque) {
    switch (message->err()) {
        case RdKafka::ERR__TIMED_OUT:

        break;
        case RdKafka::ERR_NO_ERROR:
            /* Real message */
            std::cout << "Read msg at offset " << message->offset() << std::endl;
            if (message->key()) {
              std::cout << "Key: " << *message->key() << std::endl;
            }
            std::cout << static_cast<const char *>(message->payload()) << std::endl;
        break;
        case RdKafka::ERR__PARTITION_EOF:
            std::cout << "reach last message" << std::endl;
            /* Last message */
            if (exit_eof) {
                run = false;
            }
        break;
        case RdKafka::ERR__UNKNOWN_TOPIC:
        case RdKafka::ERR__UNKNOWN_PARTITION:
            std::cerr << "Consume failed: " << message->errstr() << std::endl;
            run = false;
            break;
        default:
            /* Errors */
            std::cerr << "Consume failed: " << message->errstr() << std::endl;
            run = false;
    }
}
