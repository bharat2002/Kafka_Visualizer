#include "topicmonitoring.h"
#include <qheaderview.h>
#include <qlineedit.h>
TopicMonitoring::TopicMonitoring(QWidget *parent,std::string a_IP, std::string a_port)
    : QWidget{parent}
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QGridLayout* gridLayout = new QGridLayout(this);
    BoxLabel = new QVBoxLayout(this);
    BoxData = new QVBoxLayout(this);
    // m_DescriptionBox = new QGroupBox(this);
    m_kafkaconsumer = new KafkaConsumer(a_IP,a_port,this);
    m_TopicDropdown = new QComboBox(this);
    qDebug()<<a_IP<<a_port;
    m_TopicCountstr     = new QLabel(this);
    m_TopicCount        = new QLabel(this);
    m_DropDownLabel     = new QLabel(this);
    m_TopicDescription  = new QLabel(this);
    m_TopicName         = new QLabel(this);
    m_TimerRefreshPartitions =  new QTimer(this);
    m_TimerRefreshTopics = new QTimer(this);
    m_topicFetcher = new TopicFetcher(m_kafkaconsumer,this);
    QThread* fetchThread = new QThread(this);
    m_topicFetcher->moveToThread(fetchThread);
    // m_partitionId       = new QLabel(this);
    // m_Leader            = new QLabel(this);
    // m_Replicas          = new QLabel(this);
    // m_ISRs              = new QLabel(this);
    // m_PartitionError    = new QLabel(this);
    // m_partitionIdData       = new QLabel(this);
    // m_LeaderData            = new QLabel(this);
    // m_ReplicasData          = new QLabel(this);
    // m_ISRsData              = new QLabel(this);
    // m_PartitionErrorData    = new QLabel(this);
    // searchBar = new QLineEdit(this);
    // searchBar->setPlaceholderText("Search partitions...");
    m_TopicCountstr->setText(tr("🟢 Total Available Topics: "));
    m_TopicCount->setText(QString::number(0));
    m_DropDownLabel->setText("📜 List of Available Topics:");
    m_TopicDescription->setText("📌 Topic Description:");
    // m_partitionId->setText("Partition Id: ");
    // m_Leader->setText("Leader: ");
    // m_Replicas->setText("Replicas: ");
    // m_ISRs->setText("ISRs: ");
    // m_PartitionError->setText("Partition Error: ");
    // m_partitionIdData->setText("");
    // m_LeaderData->setText("");
    // m_ReplicasData->setText("");
    // m_ISRsData->setText("");
    // m_PartitionErrorData->setText("");
    partitionTree = new QTreeWidget(this);
    partitionTree->setWordWrap(true);
    partitionTree->setColumnCount(4);
    partitionTree->setHeaderLabels({"Partition", "Replication Factor", "Leader", "ISR"});
    partitionTree->header()->setSectionResizeMode(QHeaderView::Stretch);
    partitionTree->setStyleSheet("border: 1px solid #ccc;");
    QString labelStyle = "QLabel { font-size: 14px; color: #cccccc; }";
    m_TopicDescription->setStyleSheet("font-size: 20px; font-weight: bold; color: #ffffff;");
    m_TopicCountstr     ->setStyleSheet(labelStyle);
    m_TopicCount        ->setStyleSheet(labelStyle);
    m_DropDownLabel     ->setStyleSheet(labelStyle);
    m_TopicName->setStyleSheet(labelStyle);
    m_TopicCountstr->setFixedWidth(250);  // Example fixed width
    m_TopicCount->setFixedWidth(50);
    m_DropDownLabel->setFixedWidth(250);
    m_TopicDropdown->setFixedWidth(500);
    m_TopicDescription->setFixedWidth(400);
    gridLayout->setContentsMargins(10, 10, 10, 10);  // Left, Top, Right, Bottom
    gridLayout->setSpacing(5);  // Space between widgets
    gridLayout->setAlignment(Qt::AlignTop);
    mainLayout->setAlignment(Qt::AlignTop);
    // gridLayout->setSizeConstraint(QLayout::SetFixedSize);
     m_TopicDropdown->addItems({"Topic A", "Topic B", "Topic C"});
    gridLayout->addWidget(m_TopicCountstr,0,0,Qt::AlignLeft);
    gridLayout->addWidget(m_TopicCount,0,1,Qt::AlignLeft);
    gridLayout->addWidget(m_DropDownLabel,1,0,Qt::AlignLeft);
    gridLayout->addWidget(m_TopicDropdown,2,0, Qt::AlignTop );
    mainLayout->addLayout(gridLayout);
    mainLayout->addWidget(m_TopicDescription,0,Qt::AlignHCenter);
    mainLayout->addWidget(partitionTree);

    // connect(m_kafkaconsumer,&KafkaConsumer::newTopicDetected,this,&TopicMonitoring::onNewTopic);
    connect(m_kafkaconsumer, &KafkaConsumer::newMessageReceived, this, &TopicMonitoring::handleNewMessage);
    connect(m_TopicDropdown, &QComboBox::currentTextChanged, this, &TopicMonitoring::handleTopicSelection);
    connect(m_TimerRefreshTopics, &QTimer::timeout, m_topicFetcher, &TopicFetcher::fetchTopics);
    connect(m_topicFetcher,&TopicFetcher::topicsFetched,this,&TopicMonitoring::onNewTopic);
    connect(m_TimerRefreshPartitions,&QTimer::timeout,this, &TopicMonitoring::UpdatePartitionList);
    m_TimerRefreshTopics->start(5000);
    // m_TimerRefreshPartitions->start(1000);
    // UpdatePartitionList();
    // updatePartitionTree("testtopic");
}

void TopicMonitoring::onNewTopic(std::vector<std::string> topics)
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

}

void TopicMonitoring::handleTopicSelection(const QString &topic)
{

}


void TopicMonitoring::updatePartitionTree(const QString &topic) {
    partitionTree->clear();

    // Simulated data: topic -> partitions
    // topicData = {
    //     {"Topic A", {{"0", "3", "Broker 1", "Broker 1, Broker 2"},
    //                  {"1", "3", "Broker 2", "Broker 1, Broker 2, Broker 3"}}},

    //     {"Topic B", {{"0", "2", "Broker 3", "Broker 3, Broker 4"},
    //                  {"1", "2", "Broker 4", "Broker 3, Broker 4"}}},

    //     {"Topic C", {{"0", "1", "Broker 5", "Broker 5"}}}
    // };

    int partitionCount = topicData[topic].size();
    int maxReplication = 0;

    for (const auto &partition : topicData[topic]) {
        QTreeWidgetItem *partitionItem = new QTreeWidgetItem(partitionTree);
        for (int i = 0; i < partition.size(); ++i) {
            partitionItem->setText(i, partition[i]);
        }
        partitionTree->addTopLevelItem(partitionItem);
        maxReplication = std::max(maxReplication, partition[1].toInt());
    }

    // Update info label

}

void TopicMonitoring::filterPartitions(const QString &searchText) {
    for (int i = 0; i < partitionTree->topLevelItemCount(); ++i) {
        QTreeWidgetItem *item = partitionTree->topLevelItem(i);
        bool match = item->text(0).contains(searchText, Qt::CaseInsensitive);
        item->setHidden(!match);
    }
}

void TopicMonitoring::UpdatePartitionList()
{
    m_kafkaconsumer->getTopicsData(topicData);
}
