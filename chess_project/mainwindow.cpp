#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui->graphicsMainView->setScene(scene);
    QBrush blackBrush(Qt::black);
    QBrush whiteBrush(Qt::white);
    QPen blackPen(Qt::black);
    bool color = false;
    changeStatusText(Controller::getStatus(board));

    for(int i = 0; i < 8; i++){
        for(int j = 0 ; j < 8; j++){
            if ((i + j) %2 == 0) continue;
            QGraphicsRectItem *tmpRect = scene->addRect(i*squareSize, j*squareSize, squareSize, squareSize, blackPen, blackBrush);
        }
    }
    drawBoard();

}

void MainWindow::changeStatusText(std::string text){
    ui->statusLabel->setText(QString::fromStdString(text));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBoard(){
    for(int i = 0; i < 8; i++){
        for(int j = 0 ; j < 8; j++){
            int x = i;
            int y = 7-j;
            if (board.board[x][y] == 0) continue;
            drawPiece(i*squareSize,j*squareSize,board.board[x][y],scene);
        }
    }

}

void MainWindow::deleteAllPieces(){
    for(int i = pieces.size()-1; i >=0 ; i--){
        delete (pieces.at(i));
    }
    pieces.clear();
}

void MainWindow::drawPiece(int x, int y, int piece, QGraphicsScene *scene){

    QImage *myImg = new QImage;
    QString path = QString::fromStdString(pieceIndextoPiece(piece));
    myImg->load(path);
    QImage newImg = myImg->scaled(50, 50);
    QPixmap pix;
    pix = pix.fromImage(newImg, Qt::AutoColor );
    QGraphicsPixmapItem *m = new QGraphicsPixmapItem(pix);
    m->setZValue(50);
    m->setPos(x, y);
    scene->addItem(m);
    pieces.push_back(m);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int x = (event->x()-200)/49;
    int y = (event->y()-100)/49;
    if ( (x < 0) || (x >= 8) || (y < 0) || (y >=8)) return;
    if (choosingMove == false){
        currentMove.startX = x;
        currentMove.startY = 7-y;
        choosingMove = true;
    }
    else{
        currentMove.endX = x;
        currentMove.endY = 7-y;

        qInfo("making a move, from (%d,%d) to (%d,%d) \n", currentMove.startX,currentMove.startY,currentMove.endX,currentMove.endY);

        if (Controller::valid(board,currentMove)){
            qInfo("move made");
            board = Controller::move(board,currentMove);
            board = Controller::nextTurn(board);
            qInfo("Modifying board");
            deleteAllPieces();
            qInfo("deleted pieces\n");
            drawBoard();
            changeStatusText(Controller::getStatus(board));
            choosingMove = false;
        }
        else{
            choosingMove = false;
            qInfo("failed in making a move\n");
        }
    }
    qInfo("x:%d y:%d\n",(event->x()-200)/49,(event->y()-100)/49);

    //deleteAllPieces();

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_A){
        currentMove.startX = 4;
        currentMove.startY = 1;
        currentMove.endX = 4;
        currentMove.endY = 3;

    }
    else if (event->key() == Qt::Key_B){
        currentMove.startX = 6;
        currentMove.startY = 7;
        currentMove.endX = 5;
        currentMove.endY = 5;
    }
    else if (event->key() == Qt::Key_C){
        currentMove.startX = 3;
        currentMove.startY = 1;
        currentMove.endX = 3;
        currentMove.endY = 3;
    }

    board = Controller::move(board,currentMove);
    board = Controller::nextTurn(board);
    qInfo("Modifying board");
    deleteAllPieces();
    qInfo("deleted pieces\n");
    drawBoard();
    changeStatusText(Controller::getStatus(board));
    choosingMove = false;
    //deleteAllPieces();

}


std::string MainWindow::pieceIndextoPiece(int piece){
    switch (piece){
        case 1:
            return "/home/siddharth/chess_project/sprites/Chess_Pieces_golden/Pawn/pawn_new.png";
        case 2:
            return "/home/siddharth/chess_project/sprites/Chess_Pieces_golden/Bishop/bishop_new_2.png";
        case 3:
            return "/home/siddharth/chess_project/sprites/Chess_Pieces_golden/Knight/Knight_2.png";
        case 4:
            return "/home/siddharth/chess_project/sprites/Chess_Pieces_golden/Rook/Rook.png";
        case 5:
            return "/home/siddharth/chess_project/sprites/Chess_Pieces_golden/Queen/queen.png";
        case 6:
            return "/home/siddharth/chess_project/sprites/Chess_Pieces_golden/King/King_1.png";
        case 7:
            return "/home/siddharth/chess_project/sprites/Chess_pieces_Green/Pawn/pawn_new.png";
        case 8:
            return "/home/siddharth/chess_project/sprites/Chess_pieces_Green/Bishop/bishop_new_2.png";
        case 9:
             return "/home/siddharth/chess_project/sprites/Chess_pieces_Green/Knight/Knight_1.png";
        case 10:
             return "/home/siddharth/chess_project/sprites/Chess_pieces_Green/Rook/Rook.png";
        case 11:
             return "/home/siddharth/chess_project/sprites/Chess_pieces_Green/Queen/queen.png";
        case 12:
             return "/home/siddharth/chess_project/sprites/Chess_pieces_Green/King/King_1.png";


    }
}

