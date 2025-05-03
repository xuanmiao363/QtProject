#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "player.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QPalette>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* 创建棋盘对象 */
    chessBoard = new ChessBoard(this);

    /* 设置mainwindow窗口大小和名称*/
    setFixedSize(800,800);
    setWindowTitle("五子棋");

    /*设置棋盘布局*/
    QWidget *centerWidget = new QWidget();
    setCentralWidget(centerWidget);
    QBoxLayout *layout = new QVBoxLayout(centerWidget);
    layout->addWidget(chessBoard);

    /* 创建棋手对象 */
    player = new Player(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

