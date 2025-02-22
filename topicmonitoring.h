#ifndef TOPICMONITORINGTAB_H
#define TOPICMONITORINGTAB_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QTimer>
#include <QtCharts/qchartview.h>
#include <QtCharts/qlineseries.h>
#include <librdkafka/rdkafkacpp.h>



class TopicMonitoringTab : public QWidget {
    Q_OBJECT

public:
    explicit TopicMonitoringTab(QWidget *parent = nullptr);
    ~TopicMonitoringTab();

private slots:
    void updateTopicMetrics();

private:
    QTableWidget *topicTable;
    QChartView *chartView;
    QLineSeries *messageRateSeries;
    QTimer *updateTimer;

    RdKafka::KafkaConsumer* consumer;
    RdKafka::Conf* config;
};

#endif // TOPICMONITORINGTAB_H
