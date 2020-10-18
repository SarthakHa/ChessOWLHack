#include "controller.h"
#include <iostream>
#include <vector>
using namespace std;

int Controller::determine_piece(int x, int y, Chessboard currentBoard)
{
  return currentBoard.board[x][y];
}

bool Controller::valid(Chessboard currentBoard, PlayerMove player_move)
{
    int startX = player_move.startX;
    int startY = player_move.startY;
    int endX = player_move.endX;
    int endY = player_move.endY;
    if(startX == endX && startY == endY)
        return false;
    if(startX < 0 || startX > 8 || startY < 0 || startY > 8)
        return false;
    int piece = currentBoard.board[player_move.startX][player_move.startY];
    if (piece == 0)
        return false;
    if (piece < 7 && determine_piece(endX, endY, currentBoard) < 7 && determine_piece(endX, endY, currentBoard) > 0)
        return false;
    if (piece > 6 && determine_piece(endX, endY, currentBoard) > 6)
        return false;
    if ((piece < 7 && !currentBoard.turn) || (piece > 6 && currentBoard.turn))
        return false;

    //white pawn
    if(piece == 1)
    {
        if((abs(startX-endX) == 1) && ((startY+1) == endX) && determine_piece(endX, endY, currentBoard) > 6)
            return true;
        if(determine_piece(endX, endY, currentBoard)!= 0)
            return false;
        if(startX == endX && startY + 1 == endY)
            return true;
        if(startX == endX && startY + 2 == endY && startY==1 && determine_piece(startX, startY+1, currentBoard)==0)
            return true;
        return false;
    }

    //black pawn
    if(piece == 7)
    {
        if((abs(startX-endX) == 1) && ((startY-1) == endX) && determine_piece(endX, endY, currentBoard) < 7)
            return true;
        if(determine_piece(endX, endY, currentBoard)!= 0)
            return false;
        if(startX == endX && startY - 1 == endY)
            return true;
        if(startX == endX && startY - 2 == endY && startY == 6 && determine_piece(startX, startY+1, currentBoard) == 0)
            return true;
        return false;
    }

    //bishops
    if (piece == 2 || piece == 8)
    {
        if (abs(startX-endX)!=abs(startY-endY))
            return false;
        int slope = (endX-startX)/(endY-startY);
        //if slope is positive, slope is positive
        int direction = (endX-startX)/abs(endX-startX);
        //if direction is positive, bishop goes to the right
        for (int i = 1; i < abs(endX-startX); i++)
            if(determine_piece(startX + (direction * i), startY + (slope * direction * i), currentBoard)!=0)
                return false;
        return true;
    }

    //kings
    if (piece == 6)
    {
        if (abs(startX-endX) < 2 && abs(startY-endY) < 2)
            return true;
        //if castled is false and rook
        //if(!currentBoard.castled[currentBoard.turn] &&)
        return false;
    }

    if(piece == 12)
    {
        if (abs(startX-endX) < 2 && abs(startY-endY) < 2)
            return true;
        return false;
    }

    //rooks
    if (piece == 4 || piece == 10)
    {
        if(endX == startX)
        {
            int direction = (endY-startY)/(abs(startY-endY));
            for(int i = 1; i < abs(endY - startY) - 1; i++) //check
                if(determine_piece(startX, startY + (i*direction), currentBoard) != 0)
                    return false;
            return true;
        }
        if(endY == startY)
        {
            int direction = (endX - startX)/(abs(startX - endX));
            for(int i = 1; i < abs(endX - startX); i++) //check
                if(determine_piece(startX + (i*direction), startY, currentBoard) != 0)
                    return false;
            return true;
        }
        return false;
    }

    //queens
    if (piece == 5 or piece == 11)
    {
        if (abs(startX - endX) == abs(startY - endY))
        {
            int slope = (endX - startX)/(endY - startY);
            int direction = (endX - startX)/abs(endX - startX);
            //if direction is positive, bishop goes to the right
            for (int i = 1; i < abs(endX - startX); i++)
                if(determine_piece(startX + (direction * i), startY + (slope * direction * i), currentBoard)!=0)
                    return false;
            return true;
        }
        if(endX == startX)
        {
            int direction = (endY-startY)/(abs(startY-endY));
            for(int i = 1; i < abs(endY - startY); i++)
                if(determine_piece(startX, startY + (i*direction), currentBoard) != 0)
                    return false;
            return true;
        }
        if(endY == startY)
        {
            int direction = (endX - startX)/(abs(startX - endX));
            for(int i = 1; i < abs(endX - startX); i++)
                if(determine_piece(startX + (i*direction), startY, currentBoard) != 0)
                    return false;
            return true;
        }
        return false;
    }

    if (piece == 3 or piece == 9)
    {
        if ((abs(startX-endX)==1 and abs(startY-endY)==2) or (abs(startX-endX)==2 and abs(startY-endY)==1))
          return true;
        else
          return false;
    }

    return false;

}

Controller::Chessboard Controller::move(Chessboard currentBoard, PlayerMove player_move)
{
    currentBoard.board[player_move.endX][player_move.endY] = determine_piece(player_move.startX, player_move.startY, currentBoard);
    currentBoard.board[player_move.startX][player_move.startY] = 0;
    return currentBoard;
    //if king moves then castled is true
    //if king moved two spaces then castled is true, move rook
}

Controller::Chessboard Controller::newBoard()
{
    Controller::Chessboard newBoard;
    newBoard.board = {
        {4, 1, 0, 0, 0, 0, 7, 10},
        {3, 1, 0, 0, 0, 0, 7, 9},
        {2, 1, 0, 0, 0, 0, 7, 8},
        {5, 1, 0, 0, 0, 0, 7, 11},
        {6, 1, 0, 0, 0, 0, 7, 12},
        {2, 1, 0, 0, 0, 0, 7, 8},
        {3, 1, 0, 0, 0, 0, 7, 9},
        {4, 1, 0, 0, 0, 0, 7, 10}};
    newBoard.turn = true;
    newBoard.castled = {false, false};
    return newBoard;
}

//returns
string Controller::getStatus(Chessboard currentBoard)
{
    bool wk = false;
    bool bk = false;
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            if(currentBoard.board[i][j] == 6)
                wk = true;
            else if(currentBoard.board[i][j] == 12)
                bk = true;
        }
    }

    if(!wk)
        return "Black Wins";

    if(!bk)
        return "White Wins";

    if(currentBoard.turn)
        return "White's Turn";

    return "Black's Turn";
}

Controller::Chessboard Controller::nextTurn(Chessboard currentBoard)
{
    currentBoard.turn = !currentBoard.turn;
    return currentBoard;
}
//bool Controller::test_check(Chessboard currentBoard, PlayerMove player_move);
//bool Controller::test_checkmate(Chessboard currentBoard, PlayerMove player_move);
//X Y
