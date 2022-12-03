#ifndef PLAYER_H
#define PLAYER_H

#include "Move.h"
#include "ChessBoard.h"

class Player { 
    protected: 
        Move castleMoveCreator(Move move);
    private:
        bool color;
        bool inCheck;
        bool hasCastled;
        bool isComputer;
        ChessBoard *board;

    public:
        Player(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
        virtual ~Player();
        void setInCheck(bool inCheck);
        void setHasCastled(bool hasCastled);
        ChessBoard *getBoard();
        bool getColor();
        bool getInCheck();
        bool isCheckmate();
        bool isStalemate(); 
        bool getHasCastled();
        virtual Move handleMove() = 0; 
};

#endif 
