#ifndef PLAYER_H
#define PLAYER_H

#include <QWidget>
#include <QPushButton>
#include <stdshared.h>

class Player : public QWidget
{
    Q_OBJECT

public:
    explicit Player(QWidget *parent = nullptr);

private:
    QPushButton *btn1;
    QPushButton *btn2;
    QPushButton *btn3;

signals:

public slots:
    void btn1Clicked();
    void btn2Clicked();
    void btn3Clicked();
};

#endif // PLAYER_H
