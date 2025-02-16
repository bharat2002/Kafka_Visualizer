#include "dashboard.h"
#include <QHeaderView>
#include <QVBoxLayout>
#include <iostream>
#include <qmessagebox.h>

// Constructor
Dashboard::Dashboard(QWidget *parent, std::string a_IP, std::string a_port) : QWidget(parent) {
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Cluster Info
    clusterIdLabel = new QLabel("Cluster ID: Fetching...", this);
    totalBrokersLabel = new QLabel("Total Brokers: 0", this);
    activeBrokersLabel = new QLabel("Active Brokers: 0", this);
    controllerBrokerLabel = new QLabel("Controller Broker: None", this);
    versionLabel = new QLabel("Kafka Version: Fetching...", this);
    zookeeperStatusLabel = new QLabel("Zookeeper Status: Checking...", this);

    mainLayout->addWidget(clusterIdLabel);
    mainLayout->addWidget(totalBrokersLabel);
    mainLayout->addWidget(activeBrokersLabel);
    mainLayout->addWidget(controllerBrokerLabel);
    mainLayout->addWidget(versionLabel);
    mainLayout->addWidget(zookeeperStatusLabel);

    // Broker Table
    brokerTable = new QTableWidget(this);
    brokerTable->setColumnCount(3);
    brokerTable->setHorizontalHeaderLabels({"Broker ID", "Status", "Host"});
    brokerTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    mainLayout->addWidget(brokerTable);

    // Kafka Configuration
    config = RdKafka::Conf::create(RdKafka::Conf::CONF_GLOBAL);
    std::string Errstr;
    config->set(strMetaDataBrokerList, a_IP+":"+a_port, Errstr);
    if(Errstr.empty())
    {
        QMessageBox::information(this, QString::fromStdString(Errstr),QString::fromStdString(Errstr));
    }
    else
    {
        QMessageBox::information(this, QString::fromStdString(Errstr),QString::fromStdString(Errstr));
    }

    // Timer to update metrics
    updateTimer = new QTimer(this);
    connect(updateTimer, &QTimer::timeout, this, &Dashboard::updateMetrics);
    updateTimer->start(5000); // Update every 5 seconds

    updateMetrics();
}

// Destructor
Dashboard::~Dashboard() {
    updateTimer->stop();
}

// Fetch Kafka Metrics
void Dashboard::updateMetrics() {
    RdKafka::Metadata *metadata;
    std::string Errstr ;
    RdKafka::KafkaConsumer *tempConsumer = RdKafka::KafkaConsumer::create(config,Errstr);
    if(!Errstr.empty())
    {
        qDebug()<<Errstr;
    }
    if (!tempConsumer) {
        std::cerr << "Failed to create consumer" << std::endl;
        return;
    }
    if (tempConsumer->metadata(true, nullptr, &metadata, 5000) == RdKafka::ERR_NO_ERROR) {
        clusterIdLabel->setText("Cluster ID: " + QString::fromStdString(metadata->orig_broker_name()));
        totalBrokersLabel->setText("Total Brokers: " + QString::number(metadata->brokers()->size()));

        brokerTable->setRowCount(0);
        for (auto &broker : *metadata->brokers()) {
            int row = brokerTable->rowCount();
            brokerTable->insertRow(row);
            brokerTable->setItem(row, 0, new QTableWidgetItem(QString::number(broker->id())));
            brokerTable->setItem(row, 1, new QTableWidgetItem("Active"));
            brokerTable->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(broker->host())));
            if (broker->id()) {
                controllerBrokerLabel->setText("Controller Broker: " + QString::number(broker->id()));
            }
        }
    }

    delete metadata;
    delete tempConsumer;
}
