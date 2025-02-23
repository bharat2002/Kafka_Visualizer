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
#include <QTreeWidget>
#include "TopicFetcher.h"
class TopicMonitoring : public QWidget
{
    Q_OBJECT
private slots:
    void onNewTopic();
    void handleNewMessage(const std::string &topic, const std::string &message);
    void handleTopicSelection(const QString &topic);
    void updatePartitionTree(const QString &topic);
    void filterPartitions(const QString &searchText);
    void UpdatePartitionList();
public:
    explicit TopicMonitoring(QWidget *parent = nullptr,std::string a_IP=strLocalhost, std::string a_port=strdefaultBrokerport);
private:
    KafkaConsumer* m_kafkaconsumer;
    TopicFetcher* m_topicFetcher;
    QComboBox* m_TopicDropdown;
    QTimer* topicUpdateTimer;
    std::string currentTopic;
    QTableWidget *messagesTable;
    QLabel* m_TopicCountstr;
    QLabel* m_TopicCount;
    QLabel* m_DropDownLabel;
    QLabel* m_TopicDescription;
    QLabel* m_TopicName;
    QLabel* m_partitionId;
    QLabel* m_Leader;
    QLabel* m_Replicas;
    QLabel* m_ISRs;
    QLabel* m_PartitionError;
    QLabel* m_partitionIdData;
    QLabel* m_LeaderData;
    QLabel* m_ReplicasData;
    QLabel* m_ISRsData;
    QLabel* m_PartitionErrorData;
    QGroupBox* m_DescriptionBox;
    QVBoxLayout* BoxLabel;
    QVBoxLayout* BoxData;
    QLineEdit* searchBar;
    QTreeWidget *partitionTree;
    QMap<QString, QList<QList<QString>>> topicData;
    QTimer* m_TimerRefreshTopics;
    QTimer* m_TimerRefreshPartitions;
signals:
};

#endif // TOPICMONITORING_H
