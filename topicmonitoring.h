#ifndef TOPICMONITORING_H
#define TOPICMONITORING_H

#include <QWidget>
#include <QComboBox>
#include "Defines.h"
#include "kakfaconsumer.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QTableWidget>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
class TopicMonitoring : public QWidget
{
    Q_OBJECT
private slots:
    void onNewTopic();
    void handleNewMessage(const std::string &topic, const std::string &message);
    void handleTopicSelection(const QString &topic);
public:
    explicit TopicMonitoring(QWidget *parent = nullptr,std::string a_IP=strLocalhost, std::string a_port=strdefaultBrokerport);
private:
    KafkaConsumer* m_kafkaconsumer;
    QComboBox* m_TopicDropdown;
    QTimer* topicUpdateTimer;
    std::string currentTopic;
    QTableWidget *messagesTable;
    QLabel* m_TopicCountstr;
    QLabel* m_TopicCount;
    QLabel* m_DropDownLabel;
    QLabel* m_TopicDescription;
    QLabel* m_TopicName;
    QGroupBox* m_DescriptionBox;
signals:
};

#endif // TOPICMONITORING_H
