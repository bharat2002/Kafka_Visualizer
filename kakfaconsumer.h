#ifndef KAKFACONSUMER_H
#define KAKFACONSUMER_H
#include <rdkafkacpp.h>
// #include <rdkafka.h>

class CKafkaConsumer : public RdKafka::RebalanceCb , public RdKafka::EventCb
{
private :
    void rebalance_cb(RdKafka::KafkaConsumer* consumer, RdKafka::ErrorCode err, std::vector<RdKafka::TopicPartition*>& partitions) override;
    void event_cb(RdKafka::Event& event) override;
    void consumeLoop();

    // Kafka Variables
    std::string brokers_;
    std::string groupId_;
    std::string topic_;
    RdKafka::KafkaConsumer* consumer_;
    RdKafka::Conf* config_;
    RdKafka::Conf* topicConfig_;
    bool running_;
public:
    CKafkaConsumer(const std::string& brokers, const std::string& groupId, const std::string& topic);
    virtual ~CKafkaConsumer();

};

#endif // KAKFACONSUMER_H
