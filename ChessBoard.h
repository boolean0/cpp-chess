#ifndef _CHESSBOARD_H_
#define _CHESSBOARD_H_
#include "Piece.h"
#include "Move.h"
#include "Subject.h"
#include <utility>

class ChessBoard : public Subject {
    private:
        Piece* board[8][8];
        void trySetPiece(Move move);
        void resetMove(Move move);
        bool isPotentialMove(Move move); 
        void afterMove(Move move); 
        bool checkLegalCastle(Move move, bool isKSCastle);
        Move castlingKingMoveFactory(Move kingMove, pair<int, int> ending, bool isKSCastle);
    public:
        ~ChessBoard();
        void init(); 
        bool isPathClear(Move move);
        bool isInCheck(bool white);
        bool simulateMove(Move move); 
        Piece* getPiece(pair<int, int> square);
        void setPiece(pair<int, int> square, Piece* piece); 
        bool checkInDanger(Piece* piece); 
        bool isOccupied(pair<int, int> square);
        bool checkMoveLegal(Move move);
        void printCLI();
        void doMove(Move move);
        bool isCheckMove(Move move);
        bool isMovingOutOfDanger(Move move);
};

#endif
