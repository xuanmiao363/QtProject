#include "player.h"
#include <QDebug>

Player::Player(QWidget *parent) : QWidget(parent)
{
    /* 设置黑棋 */
    btn1 = new QPushButton;
    btn1->setParent(parent);
    btn1->setText("黑棋");
    QPalette palette1 = btn1->palette();
    palette1.setColor(QPalette::ButtonText, QColor(255, 255, 255));
    palette1.setColor(QPalette::Button, QColor(0, 0, 0));
    btn1->setPalette(palette1);
    btn1->move(350, 20);
    btn1->resize(100,50);
    btn1->setEnabled(true);

    /* 设置白棋 */
    btn2 = new QPushButton;
    btn2->setParent(parent);
    btn2->setText("白棋");
    QPalette palette2 = btn2->palette();
    palette2.setColor(QPalette::ButtonText, QColor(0, 0, 0));
    palette2.setColor(QPalette::Button, QColor(255, 255, 255));
    btn2->setPalette(palette2);
    btn2->move(350, 700);
    btn2->resize(100,50);
    btn2->setEnabled(true);

    // 连接按钮的点击信号到自定义信号
    connect(btn1, &QPushButton::clicked, this, &Player::btn1Clicked);
    connect(btn2, &QPushButton::clicked, this, &Player::btn2Clicked);
}




