#ifndef KAFKACONSUMER_H
#define KAFKACONSUMER_H

#include <QObject>
#include <librdkafka/rdkafkacpp.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

class KafkaConsumer : public QObject {
    Q_OBJECT

public:
    explicit KafkaConsumer(const std::string brokers,std::string port, QObject *parent = nullptr);
    ~KafkaConsumer();

    std::vector<std::string> getTopicList();
    void startConsumerForTopic(const std::string &topic);
    void stopConsumerForTopic(const std::string &topic);

signals:
    void newTopicDetected(const std::string &topic);
    void topicRemoved(const std::string &topic);
    void newMessageReceived(const std::string &topic, const std::string &message);

private:
    std::unique_ptr<RdKafka::Conf> config;
    std::unique_ptr<RdKafka::KafkaConsumer> globalConsumer;
    std::map<std::string, std::unique_ptr<RdKafka::KafkaConsumer>> topicConsumers;
    std::string brokers;
};

#endif // KAFKACONSUMER_H
