#include "kakfaconsumer.h"
#include <iostream>


CKafkaConsumer::CKafkaConsumer(const std::string& brokers, const std::string& groupId, const std::string& topic)
    : brokers_(brokers), groupId_(groupId), topic_(topic), consumer_(nullptr), config_(nullptr), topicConfig_(nullptr), running_(false) {
    // Constructor logic here
}

CKafkaConsumer::~CKafkaConsumer() {
    if (consumer_) {
        consumer_->close();
        delete consumer_;
    }
    delete config_;
    delete topicConfig_;
}

// Proper implementation of the virtual function
void CKafkaConsumer::rebalance_cb(RdKafka::KafkaConsumer* consumer, RdKafka::ErrorCode err, std::vector<RdKafka::TopicPartition*>& partitions) {
    std::cout << "Rebalance callback called!" << std::endl;
}

void CKafkaConsumer::event_cb(RdKafka::Event& event) {
    std::cout << "Event callback called!" << std::endl;
}
