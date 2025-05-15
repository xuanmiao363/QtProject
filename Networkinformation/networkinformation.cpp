#include "networkinformation.h"
#include "ui_networkinformation.h"
#include <QHostInfo>
#include <QDebug>

NetworkInformation::NetworkInformation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkInformation)
{
    ui->setupUi(this);
    setupWindow(this); //调用封装函数setupWindow
    getHostInformation();
}

/* 封装函数setupWindow */
void NetworkInformation::setupWindow(QWidget *parent)
{
    parent->setFixedSize(250,200);
    parent->move(750,300);
    hostLabel = new QLabel(tr("主机名"));
    ipLabel = new QLabel(tr("IP 地址"));

    lineEditLocalHostName = new QLineEdit();
    lineEditLocalHostName->setFixedWidth(150);

    lineEditAddress = new QLineEdit();
    lineEditAddress->setFixedWidth(150);

    detailButton = new QPushButton(tr("详细"));

    mainLayout = new QGridLayout(parent);
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(lineEditLocalHostName,0,1);

    mainLayout->addWidget(ipLabel, 1, 0);
    mainLayout->addWidget(lineEditAddress,1,1);
    mainLayout->addWidget(detailButton, 2,0,1,2);
}


void NetworkInformation::getHostInformation()
{
    QString localHostName = QHostInfo::localHostName();
    qDebug() << localHostName << endl;
    lineEditLocalHostName->setText(localHostName);

    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();

    lineEditAddress->setText(listAddress.at(2).toString());
}

NetworkInformation::~NetworkInformation()
{
    delete ui;
}

