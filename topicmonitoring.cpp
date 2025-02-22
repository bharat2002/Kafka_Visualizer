#include "topicmonitoring.h"
#include <qheaderview.h>

TopicMonitoring::TopicMonitoring(QWidget *parent,std::string a_IP, std::string a_port)
    : QWidget{parent}
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    m_kafkaconsumer = new KafkaConsumer(a_IP,a_port,this);
    qDebug()<<a_IP<<a_port;
    connect(m_kafkaconsumer,&KafkaConsumer::newTopicDetected,this,&TopicMonitoring::onNewTopic);
    connect(m_kafkaconsumer, &KafkaConsumer::newMessageReceived, this, &TopicMonitoring::handleNewMessage);

    m_TopicDropdown = new QComboBox(this);
    connect(m_TopicDropdown, &QComboBox::currentTextChanged, this, &TopicMonitoring::handleTopicSelection);
    mainLayout->addWidget(m_TopicDropdown);

    messagesTable = new QTableWidget(this);
    messagesTable->setColumnCount(1);
    messagesTable->setHorizontalHeaderLabels({"Live Messages"});
    messagesTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    messagesTable->horizontalHeader()->setStretchLastSection(true);
    mainLayout->addWidget(messagesTable);
    topicUpdateTimer = new QTimer(this);
    connect(topicUpdateTimer, &QTimer::timeout, this, &TopicMonitoring::onNewTopic);
    topicUpdateTimer->start(5000);

}

void TopicMonitoring::onNewTopic()
{
    m_TopicDropdown->clear();
    for(std::string topic : m_kafkaconsumer->getTopicList())
    {
        m_TopicDropdown->addItem(QString::fromStdString(topic));
        m_kafkaconsumer->startConsumerForTopic(topic);
    }
}

void TopicMonitoring::handleNewMessage(const std::string &topic, const std::string &message)
{
    if (topic != currentTopic ) return;

    messagesTable->insertRow(0);
    messagesTable->setItem(0, 0, new QTableWidgetItem(QString::fromStdString(message)));
}

void TopicMonitoring::handleTopicSelection(const QString &topic)
{
    if (currentTopic == topic.toStdString()) return;  // No change

    currentTopic = topic.toStdString();
    qDebug() << "Switched to topic:" << currentTopic.c_str();


}
