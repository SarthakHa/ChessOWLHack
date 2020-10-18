#include "controller.h"
#include <iostream>
#include <vector>
using namespace std;

int main(int argc, const char * argv[]) {

    Controller::Chessboard testBoard = Controller::newBoard();

    cout << testBoard.turn << endl;
    cout << Controller::getStatus(testBoard) << endl;
    testBoard = Controller::nextTurn(testBoard);
    cout << Controller::getStatus(testBoard) << endl;
    cout << testBoard.turn << endl;
    testBoard.board[4][0] = 0;
    cout << Controller::getStatus(testBoard) << endl;

    /*
    Controller::PlayerMove move;
    /*
    move.startX = 1;
    move.startY = 0;
    move.endX = 0;
    move.endY = 2;
    cout << Controller::valid(testBoard, move) << endl;

    move.startX = 4;
    move.startY = 1;
    move.endX = 4;
    move.endY = 2;
    cout << Controller::valid(testBoard, move) << endl;

    move.startX = 5;
    move.startY = 1;
    move.endX = 5;
    move.endY = 3;
    cout << Controller::valid(testBoard, move) << endl;

    move.startX = 6;
    move.startY = 0;
    move.endX = 7;
    move.endY = 2;
    cout << Controller::valid(testBoard, move) << endl;

    move.startX = 3;
    move.startY = 1;
    move.endX = 3;
    move.endY = 2;
    cout << Controller::valid(testBoard, move) << endl;
    */

/*
    move.startX = 3;
    move.startY = 1;
    move.endX = 3;
    move.endY = 2;

    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
            cout << Controller::determine_piece(j, i, testBoard);
        cout << endl;
    }

    cout << endl;
    cout << move.startX << endl;
    cout << move.startY << endl;
    cout << move.endX << endl;
    cout << move.endY << endl;
    cout << endl;

    testBoard = Controller::move(testBoard, move);

    for(int i = 7; i >= 0; i--)
    {
        for(int j = 0; j < 8; j++)
            cout << Controller::determine_piece(j, i, testBoard);
        cout << endl;
    }

    testBoard.board[3][1] = 0;

    move.startX = 2;
    move.startY = 0;
    move.endX = 6;
    move.endY = 4;
    //cout << Controller::valid(testBoard, move) << endl;

*/
    return 0;


    //static bool valid(Chessboard currentBoard, PlayerMove player_move);
    //static Chessboard move(Chessboard currentBoard, PlayerMove player_move);
    //static Chessboard nextTurn(Chessboard currentBoard);
    //static string getStatus(Chessboard currentBoard);
}
