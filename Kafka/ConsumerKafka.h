#ifndef CONSUMERKAFKA_H
#define CONSUMERKAFKA_H

#include <Qt>
#include "kafka/src-cpp/rdkafkacpp.h"

//class THTFKafkaCpp : public

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <csignal>
#include <cstring>
#include <getopt.h>
#include <list>
#include <vector>
#include <fstream>

//using std::string;
//using std::list;
//using std::cout;
//using std::endl;
//using std::vector;
//using std::fstream;

static bool run = true;
static bool exit_eof = true;

// Save messages from kafka to msg_data array


struct protodata
{
    uint64_t uuid;
    uint64_t position;
    uint64_t next_position;
    std::string gtid;
};

static std::vector<protodata> fulltopic;



class MyEventCb : public RdKafka::EventCb {
public:
  void event_cb (RdKafka::Event &event) {
    switch (event.type())
      {
      case RdKafka::Event::EVENT_ERROR:
        std::cerr << "ERROR (" << RdKafka::err2str(event.err()) << "): " <<
          event.str() << std::endl;
        if (event.err() == RdKafka::ERR__ALL_BROKERS_DOWN)
          run = false;
        break;

      case RdKafka::Event::EVENT_STATS:
        std::cerr << "\"STATS\": " << event.str() << std::endl;
        break;

      case RdKafka::Event::EVENT_LOG:
        fprintf(stderr, "LOG-%i-%s: %s\n",
                event.severity(), event.fac().c_str(), event.str().c_str());
        break;

      default:
        std::cerr << "EVENT " << event.type() <<
          " (" << RdKafka::err2str(event.err()) << "): " <<
          event.str() << std::endl;
        break;
      }
  }
};


void msg_consume(RdKafka::Message* message, void* opaque) ;


class MyConsumeCb : public RdKafka::ConsumeCb {
public:
  void consume_cb (RdKafka::Message &msg, void *opaque) {
    msg_consume(&msg, opaque);
  }
};

static void sigterm (int sig) {
    run = false;
}

class ConsumerKafka
{
public:
    ConsumerKafka();
    ~ConsumerKafka();

    //bool LoadCppLiberary(const QString& dllName);
    //int InitKafka(int _partition, std::string broker, std::string _topic);

    int init_kafka(int partition, std::string brokers, std::string topic);
    int pull_data_from_kafka();
    void pull_data_stop();
    void destroy();

private:
    RdKafka::Conf * global_conf;
    RdKafka::Conf * topic_conf;
    std::string brokers;
    std::string errstr;
    RdKafka::Consumer *consumer;
    std::string topic_name ;
    RdKafka::Topic *topic;
    int32_t partition;
    int64_t start_offset;
    RdKafka::Message *msg;

    bool m_bRun = false;
};

#endif // CONSUMERKAFKA_H
