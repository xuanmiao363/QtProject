#include "snake.h"
#include "ui_snake.h"
#include <QRandomGenerator>
#include <QPainter>
#include <QMessageBox>

Snake::Snake(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Snake)
    , direction(RIGHT)
    , flagPause(false)
{
    ui->setupUi(this);

    setWindowTitle("贪吃蛇");
    setFixedSize(820,680);

    snake.append(QPoint(100,100));
    snake.append(QPoint(80,100));
    snake.append(QPoint(60,100));
    snake.append(QPoint(40,100));

    pointx = QRandomGenerator::global()->bounded(width());
    pointx = (pointx/20)*20;
    pointy = QRandomGenerator::global()->bounded(height());
    pointy= (pointy/20)*20;

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Snake::updateSnake);
    timer->start(200);
}

Snake::~Snake()
{
    delete ui;
}

/* 实现画蛇函数 */
void Snake::drawSnake(QPainter &painter)
{

    for(int i=0; i<snake.size(); i++)
    {
        if(i == 0)
        {
            painter.setBrush(Qt::yellow);
            painter.drawRect(snake[i].x(),snake[i].y(),20,20);
        }
        else
        {
            painter.setBrush(Qt::green);
            painter.drawRect(snake[i].x(),snake[i].y(),20,20);
        }
    }
}

/* 实现绘画事件函数 */
void Snake::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);

    drawSnake(painter);

    painter.setBrush(Qt::red);

    painter.drawEllipse(pointx, pointy, 20, 20);
}

/* 蛇移动事件函数 */
void Snake::snakeMove()
{
    QPoint newHead = snake.first();
    switch(direction)
    {
        case UP:
            newHead.ry() -= 20;
            break;
        case DOWN:
            newHead.ry() += 20;
            break;
        case LEFT:
            newHead.rx() -= 20;
            break;
        case RIGHT:
            newHead.rx() += 20;
            break;
    }
    snake.prepend(newHead);
    snake.removeLast();
}

void Snake::updateSnake()
{
    snakeMove();
    QPoint newHead = snake.first();
    if( (newHead.rx() == pointx) && (newHead.ry() == pointy))
    {
        pointx = QRandomGenerator::global()->bounded(width());
        pointx = (pointx/20)*20;
        pointy = QRandomGenerator::global()->bounded(height());
        pointy = (pointy/20)*20;

        switch (direction)
        {
        case UP:
            snake.append(QPoint((snake.last().rx()),snake.last().ry()-20));
            break;
        case DOWN:
            snake.append(QPoint((snake.last().rx()),snake.last().ry()+20));
            break;
        case LEFT:
            snake.append(QPoint((snake.last().rx()+20),snake.last().ry()));
            break;
        case RIGHT:
            snake.append(QPoint((snake.last().rx()-20),snake.last().ry()));
            break;
        }
    }
    else if(newHead.rx() == 820 || newHead.rx() == -20   ||
            newHead.ry() == 680 || newHead.ry() == -20 )
    {
        QMessageBox::information(this, "游戏结束", "超出移动范围");
        this->close();
    }

    for(QVector<QPoint>::iterator it = snake.begin()+1; it != snake.end(); it++)
    {
        if(it->rx() == newHead.rx() && it->ry() == newHead.ry())
        {
            QMessageBox::information(this, "游戏结束", "吃到自己了");
            this->close();
        }
    }

    update();
}

void Snake::keyPressEvent(QKeyEvent *event)
{
    Q_UNUSED(event);

    switch(event->key())
    {
        case Qt::Key_Up:
             direction = UP;
             break;
        case Qt::Key_Down:
             direction = DOWN;
             break;
        case Qt::Key_Left:
             direction = LEFT;
             break;
        case Qt::Key_Right:
             direction = RIGHT;
             break;
        case Qt::Key_Space:
             if(flagPause == true)
             {
                flagPause = false;
                timer->stop();
             }
             else
             {
                flagPause = true;
                timer->start(200);
             }

             break;
    }
    update();
}
