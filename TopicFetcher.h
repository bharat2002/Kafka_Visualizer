// TopicFetcher.h
#ifndef TOPICFETCHER_H
#define TOPICFETCHER_H

#include <QObject>
#include <QStringList>
#include <QDebug>
#include <QThread>

// Include your Kafka consumer header that provides getTopicList()
#include "kakfaconsumer.h"

class TopicFetcher : public QObject {
    Q_OBJECT
public:
    explicit TopicFetcher(KafkaConsumer* consumer, QObject *parent = nullptr)
        : QObject(parent), m_consumer(consumer), m_isBusy(false) {}

public slots:
    void fetchTopics() {
        // Prevent overlapping calls if the heavy work hasn't finished yet.
        if (m_isBusy) {
            qDebug() << "Fetch already in progress; skipping this timeout.";
            return;
        }
        m_isBusy = true;
        qDebug() << "Fetching topics on thread:" << QThread::currentThread();

        // Do the heavy work here. For example, fetch topic list:
        std::vector<std::string> topics = m_consumer->getTopicList();  // Heavy/blocking call

        // Emit the result when done.
        emit topicsFetched(topics);
        m_isBusy = false;
    }

signals:
    void topicsFetched(std::vector<std::string> topics);

private:
    KafkaConsumer* m_consumer;
    bool m_isBusy;
};

#endif // TOPICFETCHER_H
