#ifndef CKAFKAINPUTDIALOG_H
#define CKAFKAINPUTDIALOG_H

#include <QDialog>
#include <QObject>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
class CKafkaInputDialog : public QDialog
{
    Q_OBJECT
public:
    CKafkaInputDialog();
    QString GetBrokerIP() const { return lineBrokerEditIP->text(); }
    QString GetBrokerPort() const { return lineBrokerEditPort->text(); }
    void setBrokerIPText(std::string&);
    void setBrokerPortText(std::string&);
    QString GetZookeeperIP() const { return lineZookeeperEditIP->text(); }
    QString GetZookeeperPort() const { return lineZookeeperEditPort->text(); }
    void setZookeeperIPText(std::string&);
    void setZookeeperPortText(std::string&);
private :
    QLineEdit *lineBrokerEditIP;
    QLineEdit *lineBrokerEditPort;
    QLineEdit *lineZookeeperEditIP;
    QLineEdit *lineZookeeperEditPort;
};

#endif // CKAFKAINPUTDIALOG_H
