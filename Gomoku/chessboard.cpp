#include "chessboard.h"
#include <QPainter>
#include <QDebug>
#include <stdshared.h>
#include <player.h>
#include <QMessageBox>

int FlagBlack = 0;
int FlagWhite = 0;
int FlagGrey = 0;

int BLACKCNTRIGHT = 0;
int BLACKCNTLEFT = 0;
int BLACKCNTUP = 0;
int BLACKCNTDOWN = 0;
int BLACKCNTRIGHTUP = 0;
int BLACKCNTLEFTDOWN = 0;
int BLACKCNTRIGHTDOWN = 0;
int BLACKCNTLEFTUP = 0;

int WHITECNTRIGHT = 0;
int WHITECNTLEFT = 0;
int WHITECNTUP = 0;
int WHITECNTDOWN = 0;
int WHITECNTRIGHTUP = 0;
int WHITECNTLEFTDOWN = 0;
int WHITECNTRIGHTDOWN = 0;
int WHITECNTLEFTUP = 0;

int GREYCNTRIGHT = 0;
int GREYCNTLEFT = 0;
int GREYCNTUP = 0;
int GREYCNTDOWN = 0;
int GREYCNTRIGHTUP = 0;
int GREYCNTLEFTDOWN = 0;
int GREYCNTRIGHTDOWN = 0;
int GREYCNTLEFTUP = 0;

bool ret;

/* 构造函数 */
ChessBoard::ChessBoard(QWidget *parent) : QWidget(parent)
{
    /* 设置鼠标追踪为true */
    setMouseTracking(true);

    /* 初始化棋子 */
    for(int iLoop=0; iLoop<boardSize; iLoop++ )
    {
        for(int jLoop=0; jLoop<boardSize; jLoop++)
        {
            boardArray[iLoop][jLoop] = EMPTY;
        }
    }
}

/* 棋盘绘画事件 */
void ChessBoard::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    /* 创建画家对象 */
    QPainter painter(this); //此处需要#include <QPainter>

    /* 抗锯齿 */
    painter.setRenderHint(QPainter::Antialiasing);

    /* 设置棋盘颜色 */
    QColor background = QColor(205, 175, 149);
    painter.fillRect(rect(), background);

    /* 划棋盘线，常量boardSize、margin和cellSize定义在ChessBoard类中*/
    for(int iLoop=0; iLoop<boardSize; iLoop++)
    {
        painter.drawLine(margin, margin + iLoop*cellSize,
                         margin+(boardSize-1)*cellSize, margin +iLoop*cellSize);

        painter.drawLine(margin + iLoop*cellSize, margin,
                         margin+iLoop*cellSize, margin + (boardSize-1)*cellSize);
    }

    /* 绘制悬停点 */
    if( ((0<=hoverRow) && (hoverRow < boardSize)) &&
        ((0<=hoverCol) && (hoverCol < boardSize)) &&
        (hoverFlag == true))
    {
        painter.setBrush(Qt::red);
        painter.drawEllipse(QPoint(margin + hoverRow*cellSize, margin + hoverCol*cellSize),
                            cellSize/5, cellSize/5);
    }

    /* 绘制棋子 */
    for(int iLoop=0; iLoop<boardSize; iLoop++ )
    {
        for(int jLoop=0; jLoop<boardSize; jLoop++ )
        {
            if (boardArray[iLoop][jLoop] == WHITESIDE)
            {
                painter.setBrush(Qt::white);
                painter.drawEllipse(QPoint(margin + iLoop*cellSize, margin + jLoop*cellSize),
                                    cellSize/3, cellSize/3);
            }
            else if(boardArray[iLoop][jLoop] == BLACKSIDE)
            {
                painter.setBrush(Qt::black);
                painter.drawEllipse(QPoint(margin + iLoop*cellSize, margin + jLoop*cellSize),
                                    cellSize/3, cellSize/3);
            }
            else if(boardArray[iLoop][jLoop] == GREYSIDE)
            {
                painter.setBrush(Qt::gray);
                painter.drawEllipse(QPoint(margin + iLoop*cellSize, margin + jLoop*cellSize),
                                    cellSize/3, cellSize/3);
            }
        }
    }
}

/* 鼠标移动事件函数 */
void ChessBoard::mouseMoveEvent(QMouseEvent *event)
{
    /* 计算格子交叉点位置 */
    if(event->x() > margin - cellSize/2 &&
       event->y() > margin - cellSize/2 )
    {
        // hoverRow，hoverCol，hoverFlag在棋盘类中定义
        hoverRow = (event->x() - margin + cellSize/2) / cellSize;
        hoverCol = (event->y() - margin+ cellSize/2) / cellSize;
    }
    else
    {
        hoverRow = -1;
        hoverCol = -1;
    }

    /* 手动触发绘画事件 */
    if( ((0<=hoverRow) && (hoverRow < boardSize)) &&
        ((0<=hoverCol) && (hoverCol < boardSize)))
    {
        hoverFlag = true;
        update();
    }
    else
    {
        hoverFlag = false;
        update();
    }
}

/* 鼠标点击下棋子事件函数 */
void ChessBoard::mousePressEvent(QMouseEvent *event)
{
    hoverRow = (event->x() - margin + cellSize/2) / cellSize;
    hoverCol = (event->y() - margin+ cellSize/2) / cellSize;

    qDebug() << "FlagBlack=" << FlagBlack <<endl; // FlagBlack是表示下黑棋
    qDebug() << "FlagWhite=" << FlagWhite <<endl; // FlagWhite是表示下白棋
    qDebug() << "FlagGrey="  << FlagGrey <<endl; // FlagWhite是表示下白棋

    if( ((0<=hoverRow) && (hoverRow < boardSize)) &&
        ((0<=hoverCol) && (hoverCol < boardSize)) &&
        (FlagBlack == 1))
    {
        if(boardArray[hoverRow][hoverCol] != EMPTY)
        {
            QMessageBox::information(this, "错误", "此处已经有棋子了");
            return;
        }

        boardArray[hoverRow][hoverCol] = BLACKSIDE;
        update();
        if (true == bIsCheckBlackWin(hoverRow, hoverCol))
        {
            QMessageBox::information(this,"游戏结束", "黑棋获胜");
        }
    }
    else if(((0<=hoverRow) && (hoverRow < boardSize)) &&
            ((0<=hoverCol) && (hoverCol < boardSize)) &&
            (FlagWhite == 1))
    {
        if(boardArray[hoverRow][hoverCol] != EMPTY)
        {
            QMessageBox::information(this, "错误", "此处已经有棋子了");
            return;
        }

        boardArray[hoverRow][hoverCol] = WHITESIDE;
        update();
        if (true == bIsCheckWhiteWin(hoverRow, hoverCol))
        {
            QMessageBox::information(this,"游戏结束", "白棋获胜");
        }
    }
    else if(((0<=hoverRow) && (hoverRow < boardSize)) &&
            ((0<=hoverCol) && (hoverCol < boardSize)) &&
            (FlagGrey == 1))
    {
        if(boardArray[hoverRow][hoverCol] != EMPTY)
        {
            QMessageBox::information(this, "错误", "此处已经有棋子了");
            return;
        }

        boardArray[hoverRow][hoverCol] = GREYSIDE;
        update();
        if (true == bIsCheckGreyWin(hoverRow, hoverCol))
        {
            QMessageBox::information(this,"游戏结束", "灰棋获胜");
        }
    }
}

/* PushButton的槽函数 */
void Player::btn1Clicked()
{
    FlagBlack = 1;
    FlagWhite = 0;
    FlagGrey = 0;
    update();
}

void Player::btn2Clicked()
{
    FlagBlack = 0;
    FlagWhite = 1;
    FlagGrey = 0;
    update();
}

void Player::btn3Clicked()
{
    FlagBlack = 0;
    FlagWhite = 0;
    FlagGrey = 1;
    update();
}

/*************************************************/
/*************************************************/
/*************************************************/
/* 检测白方棋子是否获胜 */
bool ChessBoard::bIsCheckWhiteWin(int row, int col)
{
    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col] == WHITESIDE)
        {
            qDebug()<<"右侧棋子是白色的"<< endl;
            WHITECNTRIGHT++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col] == WHITESIDE)
        {
            qDebug()<<"左侧棋子是白色的"<< endl;
            WHITECNTLEFT++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row][col+i] == WHITESIDE)
        {
            qDebug()<<"上侧棋子是白色的"<< endl;
            WHITECNTUP++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row][col-i] == WHITESIDE)
        {
            qDebug()<<"下侧棋子是白色的"<< endl;
            WHITECNTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col+i] == WHITESIDE)
        {
            qDebug()<<"右上侧棋子是白色的"<< endl;
            WHITECNTRIGHTUP++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col-i] == WHITESIDE)
        {
            qDebug()<<"左下侧棋子是白色的"<< endl;
            WHITECNTLEFTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col-i] == WHITESIDE)
        {
            qDebug()<<"右下侧棋子是白色的"<< endl;
            WHITECNTRIGHTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col+i] == WHITESIDE)
        {
            qDebug()<<"左上侧棋子是白色的"<< endl;
            WHITECNTLEFTUP++;
        }
        else
        {
            break;
        }
    }

    qDebug()<<"右侧棋子个数"<< WHITECNTRIGHT << endl;
    qDebug()<<"左侧棋子个数"<< WHITECNTLEFT << endl;
    qDebug()<<"上侧棋子个数"<< WHITECNTUP << endl;
    qDebug()<<"下侧棋子个数"<< WHITECNTDOWN << endl;
    qDebug()<<"右下侧棋子个数"<< WHITECNTRIGHTUP << endl;
    qDebug()<<"左上侧棋子个数"<< WHITECNTLEFTDOWN << endl;
    qDebug()<<"左下侧棋子个数"<< WHITECNTLEFTUP << endl;
    qDebug()<<"右上侧棋子个数"<< WHITECNTRIGHTDOWN << endl;

    if( (WHITECNTRIGHT + WHITECNTLEFT + 1 >= 5) ||
        (WHITECNTUP + WHITECNTDOWN + 1 >= 5) ||
        (WHITECNTRIGHTUP + WHITECNTLEFTDOWN + 1 >= 5) ||
        (WHITECNTLEFTUP + WHITECNTRIGHTDOWN + 1 >= 5))
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    WHITECNTRIGHT = 0;
    WHITECNTLEFT = 0;
    WHITECNTUP = 0;
    WHITECNTDOWN = 0;
    WHITECNTRIGHTUP = 0;
    WHITECNTLEFTDOWN = 0;
    WHITECNTRIGHTDOWN = 0;
    WHITECNTLEFTUP = 0;

    return ret;
}

/* 检测黑方棋子是否获胜 */
bool ChessBoard::bIsCheckBlackWin(int row, int col)
{
    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col] == BLACKSIDE)
        {
            qDebug()<<"右侧棋子是黑色的"<< endl;
            BLACKCNTRIGHT++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col] == BLACKSIDE)
        {
            qDebug()<<"左侧棋子是黑色的"<< endl;
            BLACKCNTLEFT++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row][col+i] == BLACKSIDE)
        {
            qDebug()<<"上侧棋子是黑色的"<< endl;
            BLACKCNTUP++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row][col-i] == BLACKSIDE)
        {
            qDebug()<<"下侧棋子是黑色的"<< endl;
            BLACKCNTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col+i] == BLACKSIDE)
        {
            qDebug()<<"右上侧棋子是黑色的"<< endl;
            BLACKCNTRIGHTUP++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col-i] == BLACKSIDE)
        {
            qDebug()<<"左下侧棋子是黑色的"<< endl;
            BLACKCNTLEFTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col-i] == BLACKSIDE)
        {
            qDebug()<<"右下侧棋子是黑色的"<< endl;
            BLACKCNTRIGHTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col+i] == BLACKSIDE)
        {
            qDebug()<<"左上侧棋子是黑色的"<< endl;
            BLACKCNTLEFTUP++;
        }
        else
        {
            break;
        }
    }

    qDebug()<<"右侧棋子个数"<< BLACKCNTRIGHT << endl;
    qDebug()<<"左侧棋子个数"<< BLACKCNTLEFT << endl;
    qDebug()<<"上侧棋子个数"<< BLACKCNTUP << endl;
    qDebug()<<"下侧棋子个数"<< BLACKCNTDOWN << endl;
    qDebug()<<"右下侧棋子个数"<< BLACKCNTRIGHTUP << endl;
    qDebug()<<"左上侧棋子个数"<< BLACKCNTLEFTDOWN << endl;
    qDebug()<<"左下侧棋子个数"<< BLACKCNTLEFTUP << endl;
    qDebug()<<"右上侧棋子个数"<< BLACKCNTRIGHTDOWN << endl;

    if( (BLACKCNTRIGHT + BLACKCNTLEFT + 1 >= 5) ||
        (BLACKCNTUP + BLACKCNTDOWN + 1 >= 5) ||
        (BLACKCNTRIGHTUP + BLACKCNTLEFTDOWN + 1 >= 5) ||
        (BLACKCNTLEFTUP + BLACKCNTRIGHTDOWN + 1 >= 5))
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    BLACKCNTRIGHT = 0;
    BLACKCNTLEFT = 0;
    BLACKCNTUP = 0;
    BLACKCNTDOWN = 0;
    BLACKCNTRIGHTUP = 0;
    BLACKCNTLEFTDOWN = 0;
    BLACKCNTRIGHTDOWN = 0;
    BLACKCNTLEFTUP = 0;

    return ret;
}

/* 检测灰方棋子是否获胜 */
bool ChessBoard::bIsCheckGreyWin(int row, int col)
{
    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col] == GREYSIDE)
        {
            qDebug()<<"右侧棋子是黑色的"<< endl;
            GREYCNTRIGHT++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col] == GREYSIDE)
        {
            qDebug()<<"左侧棋子是黑色的"<< endl;
            GREYCNTLEFT++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row][col+i] == GREYSIDE)
        {
            qDebug()<<"上侧棋子是黑色的"<< endl;
            GREYCNTUP++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row][col-i] == GREYSIDE)
        {
            qDebug()<<"下侧棋子是黑色的"<< endl;
            GREYCNTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col+i] == GREYSIDE)
        {
            qDebug()<<"右上侧棋子是黑色的"<< endl;
            GREYCNTRIGHTUP++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col-i] == GREYSIDE)
        {
            qDebug()<<"左下侧棋子是黑色的"<< endl;
            GREYCNTLEFTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row+i][col-i] == GREYSIDE)
        {
            qDebug()<<"右下侧棋子是黑色的"<< endl;
            GREYCNTRIGHTDOWN++;
        }
        else
        {
            break;
        }
    }

    for(int i=1; i<5; i++)
    {
        if( boardArray[row-i][col+i] == GREYSIDE)
        {
            qDebug()<<"左上侧棋子是黑色的"<< endl;
            GREYCNTLEFTUP++;
        }
        else
        {
            break;
        }
    }

    qDebug()<<"右侧棋子个数"<< GREYCNTRIGHT << endl;
    qDebug()<<"左侧棋子个数"<< GREYCNTLEFT << endl;
    qDebug()<<"上侧棋子个数"<<GREYCNTUP << endl;
    qDebug()<<"下侧棋子个数"<< GREYCNTDOWN << endl;
    qDebug()<<"右下侧棋子个数"<< GREYCNTRIGHTUP << endl;
    qDebug()<<"左上侧棋子个数"<< GREYCNTLEFTDOWN << endl;
    qDebug()<<"左下侧棋子个数"<< GREYCNTLEFTUP << endl;
    qDebug()<<"右上侧棋子个数"<< GREYCNTRIGHTDOWN << endl;

    if( (GREYCNTRIGHT + GREYCNTLEFT + 1 >= 5) ||
        (GREYCNTUP + GREYCNTDOWN + 1 >= 5) ||
        (GREYCNTRIGHTUP + GREYCNTLEFTDOWN + 1 >= 5) ||
        (GREYCNTLEFTUP + GREYCNTRIGHTDOWN + 1 >= 5))
    {
        ret = true;
    }
    else
    {
        ret = false;
    }

    GREYCNTRIGHT = 0;
    GREYCNTLEFT = 0;
    GREYCNTUP = 0;
    GREYCNTDOWN = 0;
    GREYCNTRIGHTUP = 0;
    GREYCNTLEFTDOWN = 0;
    GREYCNTRIGHTDOWN = 0;
    GREYCNTLEFTUP = 0;

    return ret;
}




















