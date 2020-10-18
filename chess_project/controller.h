#ifndef controller_h
#define controller_h
#include <stdio.h>
#include <vector>
#include <string>
using namespace std;

class Controller {
public:
    Controller();
    struct PlayerMove {
        int startX;
        int startY;
        int endX;
        int endY;
    };
    struct Chessboard {
        vector< vector<int> > board;
        bool turn; //0 for black, 1 for white
        vector<bool> castled;
    };
    static bool valid(Chessboard currentBoard, PlayerMove player_move);
    //bool test_check(Chessboard currentBoard, PlayerMove player_move);
    //bool test_checkmate(Chessboard currentBoard, PlayerMove player_move);
    static int determine_piece(int x, int y, Chessboard currentBoard);
    static Chessboard move(Chessboard currentBoard, PlayerMove player_move);
    static Chessboard newBoard();
    static Chessboard nextTurn(Chessboard currentBoard);
    static string getStatus(Chessboard currentBoard);
};

#endif
