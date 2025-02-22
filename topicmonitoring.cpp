#include "topicmonitoring.h"
#include <QtCharts/qchart.h>
#include <QtCharts/qvalueaxis.h>
#include <iostream>
#include <QMessageBox>
TopicMonitoringTab::TopicMonitoringTab(QWidget *parent, std::string a_IP, std::string a_port) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Kafka Topic Table
    topicTable = new QTableWidget(this);
    topicTable->setColumnCount(3);
    topicTable->setHorizontalHeaderLabels({"Topic Name", "Partitions", "Replication Factor"});
    topicTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mainLayout->addWidget(topicTable);

    // Live Graph for Message Rate
    QChart *chart = new QChart();
    messageRateSeries = new QLineSeries();
    chart->addSeries(messageRateSeries);

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("Time (s)");
    chart->addAxis(axisX, Qt::AlignBottom);
    messageRateSeries->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Messages/sec");
    chart->addAxis(axisY, Qt::AlignLeft);
    messageRateSeries->attachAxis(axisY);

    chartView = new QChartView(chart);
    mainLayout->addWidget(chartView);

    // Kafka Configuration
    std::string Errstr;
    config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    config->set("metadata.broker.list", a_IP+":"+a_port, Errstr);
    config->set("group.id","test",Errstr);
    // Timer for fetching Kafka topic data
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &TopicMonitoringTab::updateTopicMetrics);
    updateTimer->start(5000); // Update every 5 seconds

    updateTopicMetrics();
}

TopicMonitoringTab::~TopicMonitoringTab() {
    updateTimer->stop();
}

// Fetch Topic Metrics
void TopicMonitoringTab::updateTopicMetrics() {
    RdKafka::Metadata *metadata;
    std::string Errstr;
    RdKafka::KafkaConsumer *tempConsumer = RdKafka::KafkaConsumer::create(config, Errstr);
    if (!tempConsumer) {
        std::cerr << "Failed to create Kafka consumer" << std::endl;
        return;
    }

    if (tempConsumer->metadata(true, nullptr, &metadata, 5000) == RdKafka::ERR_NO_ERROR) {
        topicTable->setRowCount(0);

        for (auto &topic : *metadata->topics()) {
            int row = topicTable->rowCount();
            topicTable->insertRow(row);

            QTableWidgetItem *topicNameItem = new QTableWidgetItem(QString::fromStdString(topic->topic()));
            topicNameItem->setFlags(topicNameItem->flags() & ~Qt::ItemIsEditable);

            QTableWidgetItem *partitionCountItem = new QTableWidgetItem(QString::number(topic->partitions()->size()));
            partitionCountItem->setFlags(partitionCountItem->flags() & ~Qt::ItemIsEditable);

            int replicationFactor = topic->partitions()->empty() ? 0 : topic->partitions()->front()->replicas()->size();
            QTableWidgetItem *replicationFactorItem = new QTableWidgetItem(QString::number(replicationFactor));
            replicationFactorItem->setFlags(replicationFactorItem->flags() & ~Qt::ItemIsEditable);

            topicTable->setItem(row, 0, topicNameItem);
            topicTable->setItem(row, 1, partitionCountItem);
            topicTable->setItem(row, 2, replicationFactorItem);
        }
    }
    else
    {
        QMessageBox::information(this,"Eror connection", "Error connecting ,Kafka Broker Down");
    }

    delete metadata;
    delete tempConsumer;
}
