#ifndef SNAKE_H
#define SNAKE_H

#include <QWidget>
#include <QVector>      /* 添加QVector头文件 */
#include <QPoint>       /* 添加Point头文件 */
#include <QPaintEvent>  /* 添加QPaintEvent头文件 */
#include <QPainter>
#include <QTimer>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class Snake; }
QT_END_NAMESPACE

enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake : public QWidget
{
    Q_OBJECT

public:
    Snake(QWidget *parent = nullptr);
    ~Snake();


private:
    Ui::Snake *ui;
    QVector<QPoint> snake; /* 声明贪吃蛇对象 */
    void drawSnake(QPainter &painter); /* 声明画蛇函数 */
    QTimer *timer;
    Direction direction;
    int pointx;
    int pointy;
    bool flagPause;

protected:
    void paintEvent(QPaintEvent *event) override;  /* 声明绘画事件函数 */
    void keyPressEvent(QKeyEvent *event) override; /* 声明键盘时间函数 */

public slots:
    void updateSnake();
    void snakeMove();
};

#endif // SNAKE_H
