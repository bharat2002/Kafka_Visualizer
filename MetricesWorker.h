#ifndef METRICSWORKER_H
#define METRICSWORKER_H

#include <QObject>
#include <QDebug>
#include <librdkafka/rdkafkacpp.h>
#include <qthread.h>
#include <string>

class MetricsWorker : public QObject {
    Q_OBJECT
public:
    // Pass the RdKafka configuration to the worker.
    explicit MetricsWorker(RdKafka::Conf* config, QObject *parent = nullptr)
        : QObject(parent), m_config(config) {}

public slots:
    // This slot performs the heavy metadata fetch.
    void fetchMetrics() {
        qDebug() << "Fetching metrics in thread:" << QThread::currentThread();
        RdKafka::Metadata *metadata = nullptr;
        std::string errStr;

        // Create a temporary consumer to fetch metadata.
        RdKafka::KafkaConsumer *tempConsumer = RdKafka::KafkaConsumer::create(m_config, errStr);
        if (!errStr.empty()) {
            qDebug() << "Consumer creation error:" << QString::fromStdString(errStr);
        }
        if (!tempConsumer) {
            qDebug() << "Failed to create consumer";
            emit metricsError("Failed to create consumer");
            return;
        }
        // Attempt to fetch metadata.
        if (tempConsumer->metadata(true, nullptr, &metadata, 500) == RdKafka::ERR_NO_ERROR) {
            emit metricsFetched(metadata);
        } else {
            emit metricsError("Error connecting, Kafka Broker Down");
        }
        // delete metadata;
        delete tempConsumer;
    }

signals:
    // Signal to send metadata back to the UI.
    void metricsFetched(RdKafka::Metadata* metadata);
    void metricsError(const QString &errorMsg);

private:
    RdKafka::Conf* m_config;
};

#endif // METRICSWORKER_H
