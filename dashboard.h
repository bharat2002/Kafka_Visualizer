#ifndef DASHBOARD_H
#define DASHBOARD_H
#include <QLabel>
#include <QTableWidget>
#include <librdkafka/rdkafkacpp.h>
#include <QTimer>
#include <QWidget>
#include "Defines.h"
#include <librdkafka/rdkafka.h>
class Dashboard : public QWidget
{
    Q_OBJECT
public:
    Dashboard(QWidget *parent = nullptr,std::string a_IP=strLocalhost, std::string a_port=strdefaultBrokerport);
    QLabel *clusterIdLabel;
    QLabel *totalBrokersLabel;
    QLabel *activeBrokersLabel;
    QLabel *controllerBrokerLabel;
    QLabel *versionLabel;
    QLabel *zookeeperStatusLabel;

    QTableWidget *brokerTable;

    // Kafka Connection
    RdKafka::KafkaConsumer* consumer;
    RdKafka::Conf* config;

    // Timer for periodic updates
    QTimer *updateTimer;
    ~Dashboard();
    int getControllerBrokerId();
private slots:
    void updateMetrics();
    void UpdateUI(RdKafka::Metadata *metadata);
signals:
};

#endif // DASHBOARD_H
