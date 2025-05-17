#ifndef NETWORKINFORMATION_H
#define NETWORKINFORMATION_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QHostInfo>
#include <QNetworkInterface>

QT_BEGIN_NAMESPACE
namespace Ui { class NetworkInformation; }
QT_END_NAMESPACE

class NetworkInformation : public QWidget
{
    Q_OBJECT

public:
    NetworkInformation(QWidget *parent = nullptr);
    ~NetworkInformation();

private:
    Ui::NetworkInformation *ui;
    QLabel *hostLabel;
    QLabel *ipLabel;

    QLineEdit *lineEditLocalHostName;
    QLineEdit *lineEditAddress;

    QPushButton *detailButton;
    QGridLayout *mainLayout;

public:
    void getHostInformation();
    void setupWindow(QWidget *parent);

public slots:
    void slotDetail();
};

#endif // NETWORKINFORMATION_H
