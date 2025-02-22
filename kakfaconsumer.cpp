#include "kakfaconsumer.h"
#include <iostream>

KafkaConsumer::KafkaConsumer(const std::string brokers,std::string port, QObject *parent) : QObject(parent), brokers(brokers) {
    std::string err;
    config = std::unique_ptr<RdKafka::Conf>(RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL));
    config->set("metadata.broker.list", brokers+":"+port, err);
    std::cout<<brokers;
    config->set("group.id","test",err);
    globalConsumer = std::unique_ptr<RdKafka::KafkaConsumer>(RdKafka::KafkaConsumer::create(config.get(), err));
    if (!globalConsumer) {
        std::cerr << "Failed to create Kafka consumer: " << err << std::endl;
    }
}

KafkaConsumer::~KafkaConsumer() {
    for (auto &consumer : topicConsumers) {
        consumer.second->close();
    }
    globalConsumer->close();
}

std::vector<std::string> KafkaConsumer::getTopicList() {
    RdKafka::Metadata *metadata;
    std::vector<std::string> topics;

    if (globalConsumer->metadata(true, nullptr, &metadata, 100) == RdKafka::ERR_NO_ERROR) {
        for (auto &topic : *metadata->topics()) {
            topics.push_back(topic->topic());
        }
    }
    delete metadata;
    return topics;
}

void KafkaConsumer::startConsumerForTopic(const std::string &topic) {
    if (topicConsumers.find(topic) != topicConsumers.end()) return;  // Already exists

    std::string err;
    std::unique_ptr<RdKafka::KafkaConsumer> consumer(RdKafka::KafkaConsumer::create(config.get(), err));
    if (consumer) {
        consumer->subscribe({topic});
        topicConsumers[topic] = std::move(consumer);
        emit newTopicDetected(topic);
    }
}

void KafkaConsumer::stopConsumerForTopic(const std::string &topic) {
    if (topicConsumers.find(topic) != topicConsumers.end()) {
        topicConsumers[topic]->close();
        topicConsumers.erase(topic);
        emit topicRemoved(topic);
    }
}
