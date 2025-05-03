#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <QWidget>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPushButton>
#include <stdshared.h>

class ChessBoard : public QWidget
{
    Q_OBJECT

public:
    explicit ChessBoard(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    static const int boardSize = 15;
    static const int cellSize = 40;
    static const int margin = 100;

    int hoverRow = 0;
    int hoverCol = 0;
    bool hoverFlag = 0;

    ROLE boardArray[boardSize][boardSize];

    bool bIsCheckBlackWin(int row, int col);
    bool bIsCheckWhiteWin(int row, int col);
    bool bIsCheckGreyWin(int row, int col);

signals:
};

#endif // CHESSBOARD_H
