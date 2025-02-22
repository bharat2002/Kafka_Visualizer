#include "ckafkainputdialog.h"

CKafkaInputDialog::CKafkaInputDialog() {
    lineBrokerEditIP = new QLineEdit(this);
    lineBrokerEditPort = new QLineEdit(this);
    lineZookeeperEditIP = new QLineEdit(this);
    lineZookeeperEditPort = new QLineEdit(this);
    QFormLayout *formLayout = new QFormLayout(this);
    formLayout->addRow("Zookeeper IP:", lineZookeeperEditIP);
    formLayout->addRow("Zookeeper Port:", lineZookeeperEditPort);
    formLayout->addRow("Broker IP:", lineBrokerEditIP);
    formLayout->addRow("Broker Port:", lineBrokerEditPort);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, this);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);
    formLayout->addRow(buttonBox);
    this->setLayout(formLayout);
}

void CKafkaInputDialog::setBrokerIPText(std::string& a_IPText)
{
    this->lineBrokerEditIP->setText(a_IPText.c_str());
}

void CKafkaInputDialog::setBrokerPortText(std::string& a_PortText)
{
    this->lineBrokerEditPort->setText(a_PortText.c_str());
}

void CKafkaInputDialog::setZookeeperIPText(std::string& a_IPText)
{
    this->lineZookeeperEditIP->setText(a_IPText.c_str());
}

void CKafkaInputDialog::setZookeeperPortText(std::string& a_PortText)
{
    this->lineZookeeperEditPort->setText(a_PortText.c_str());
}
