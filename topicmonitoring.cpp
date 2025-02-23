#include "topicmonitoring.h"
#include <qheaderview.h>

TopicMonitoring::TopicMonitoring(QWidget *parent,std::string a_IP, std::string a_port)
    : QWidget{parent}
{
    QGridLayout* mainLayout = new QGridLayout(this);
    m_kafkaconsumer = new KafkaConsumer(a_IP,a_port,this);
    m_TopicDropdown = new QComboBox(this);
    qDebug()<<a_IP<<a_port;
    m_TopicCountstr     = new QLabel(this);
    m_TopicCount        = new QLabel(this);
    m_DropDownLabel     = new QLabel(this);
    m_TopicDescription  = new QLabel(this);
    m_TopicName         = new QLabel(this);


    m_TopicCountstr->setText(tr("🟢 Total Available Topics: "));
    m_TopicCount->setText(QString::number(0));
    m_DropDownLabel->setText("📜 List of Available Topics:");
    m_TopicDescription->setText("📌 Topic Description:");

    QString labelStyle = "QLabel { font-size: 14px; color: #cccccc; }";
    m_TopicDescription->setStyleSheet("font-size: 20px; font-weight: bold; color: #ffffff;");
    m_TopicCountstr     ->setStyleSheet(labelStyle);
    m_TopicCount        ->setStyleSheet(labelStyle);
    m_DropDownLabel     ->setStyleSheet(labelStyle);
    m_TopicName->setStyleSheet(labelStyle);
    m_TopicCountstr->setFixedWidth(250);  // Example fixed width
    m_TopicCount->setFixedWidth(50);
    m_DropDownLabel->setFixedWidth(250);
    m_TopicDropdown->setFixedWidth(350);
    m_TopicDescription->setFixedWidth(400);
    mainLayout->setContentsMargins(10, 10, 10, 10);  // Left, Top, Right, Bottom
    mainLayout->setSpacing(5);  // Space between widgets
    mainLayout->setAlignment(Qt::AlignTop);
    // mainLayout->setSizeConstraint(QLayout::SetFixedSize);


    mainLayout->addWidget(m_TopicCountstr,0,0,Qt::AlignLeft);
    mainLayout->addWidget(m_TopicCount,0,1,Qt::AlignLeft);
    mainLayout->addWidget(m_DropDownLabel,1,0,Qt::AlignLeft);
    mainLayout->addWidget(m_TopicDropdown,2,0, Qt::AlignTop );
    mainLayout->addWidget(m_TopicDescription,3,0,Qt::AlignCenter);
    connect(m_kafkaconsumer,&KafkaConsumer::newTopicDetected,this,&TopicMonitoring::onNewTopic);
    connect(m_kafkaconsumer, &KafkaConsumer::newMessageReceived, this, &TopicMonitoring::handleNewMessage);
    connect(m_TopicDropdown, &QComboBox::currentTextChanged, this, &TopicMonitoring::handleTopicSelection);

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

}

void TopicMonitoring::handleTopicSelection(const QString &topic)
{

}
