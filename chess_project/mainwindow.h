#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <string>
#include <vector>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QtCore>
#include <QImage>
#include <QString>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include <QMouseEvent>
#include <QKeyEvent>

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int squareSize = 49;
    Controller::Chessboard board = Controller::newBoard();

    MainWindow(QWidget *parent = nullptr);
    void drawBoard(std::vector<std::vector <int>> v);
    QGraphicsScene *scene;
    void deleteAllPieces();
    std::vector<QGraphicsPixmapItem*> pieces;
    bool choosingMove = false;
    Controller::PlayerMove currentMove;
    void drawPiece(int x, int y, int piece, QGraphicsScene *scene);
    void changeStatusText(std::string text);
    //void mousePressEvent(QGraphicsSceneMouseEvent *event);

    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;



private:
    Ui::MainWindow *ui;
    void drawBoard();
    std::string pieceIndextoPiece(int piece);


};
#endif // MAINWINDOW_H
