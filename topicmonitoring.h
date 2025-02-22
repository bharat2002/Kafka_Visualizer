#ifndef TOPICMONITORING_H
#define TOPICMONITORING_H

#include <QWidget>
#include <QComboBox>
#include "Defines.h"
#include "kakfaconsumer.h"
#include <QVBoxLayout>
#include <QTimer>
#include <QTableWidget>
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
signals:
};

#endif // TOPICMONITORING_H
