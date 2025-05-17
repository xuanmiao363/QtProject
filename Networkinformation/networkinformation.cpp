#include "networkinformation.h"
#include "ui_networkinformation.h"
#include <QHostInfo>
#include <QMessageBox>
#include <QDebug>

NetworkInformation::NetworkInformation(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::NetworkInformation)
{
    ui->setupUi(this);
    setupWindow(this); //调用封装函数setupWindow
    getHostInformation();
    connect(detailButton, SIGNAL(clicked()), this, SLOT(slotDetail()));
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
    lineEditLocalHostName->setText(localHostName);

    QHostInfo hostInfo = QHostInfo::fromName(localHostName);
    QList<QHostAddress> listAddress = hostInfo.addresses();

    lineEditAddress->setText(listAddress.at(2).toString());
}

void NetworkInformation::slotDetail()
{
    qDebug() << "调试： " << endl;
    QString detail = "";
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();

    for(int i=0; i<list.count(); i++)
    {
        QNetworkInterface interface = list[i];
        detail = detail +tr("网络接口：") + interface.name() + "\n";
        detail = detail +tr("Mac地址 ") + interface.hardwareAddress() + "\n";

        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        for(int j=1; j<entryList.count(); j++)
        {
            QNetworkAddressEntry entry = entryList[j];
            detail += "\t" + tr("IP地址: ") + entry.ip().toString() + "\n";
            detail += "\t" + tr("子网掩码: ") + entry.netmask().toString() + "\n" + "\n";
        }

        detail += "\n";
    }

    qDebug() << "调试： " << detail << endl;

    QMessageBox::information(this, tr("Detail"), detail);
}

NetworkInformation::~NetworkInformation()
{
    delete ui;
}

