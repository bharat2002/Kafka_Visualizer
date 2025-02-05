#ifndef CONSUMERTAB_H
#define CONSUMERTAB_H

#include <QObject>
#include "kakfaconsumer.h"
#include <QWidget>

class CConsumerTab : public QWidget
{
    Q_OBJECT
public:
    explicit CConsumerTab(QWidget *parent = nullptr);
private:
    long long m_nMessageCount = 0;
    CKafkaConsumer* m_KafkaConusmer = nullptr;
    QArrayData* m_DataTypeArray = nullptr;

signals:
};

#endif // CONSUMERTAB_H
