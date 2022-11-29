#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
#include <utility>
#include "Subject.h"
#include "Piece.h"
#include "Move.h"


class ChessBoard: public Subject {
    private:
        Piece* board[8][8];
    
    public: 
        ~ChessBoard();
        void init(); 
        bool isPathClear(Move move);
        bool isInCheck(bool white);
        void setup(); 
        Piece* getPiece(pair<int, int> square);
        void setPiece(pair<int, int> square, Piece* piece); 
        bool checkInDanger(); 
        bool isOccupied(pair<int, int> square);
        bool checkMoveLegal(Move move);
        void printCLI();
        void doMove(Move move);
};

#endif
