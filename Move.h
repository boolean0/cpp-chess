#ifndef MOVE_H
#define MOVE_H
#include <utility>
#include "Piece.h"

using namespace std;
class Move {
    private:
    Piece* movedPiece;
    pair<int,int> startPos;
    pair<int, int> endPos; 
    Piece* capturedPiece;
    bool isCastleK; 
    bool isCastleQ;
    bool isPromoting; 
    char promoteTo; 
    bool isEP; 
    
    public: 
    // two ctors: one for regular moves and one for "special" things like castling, promotion, etc.
    // regular move ctor will set all the stuff as false
    Move(Piece* movedPiece, pair<int, int> startPos, pair<int,int> endPos, Piece* capturedPiece = nullptr);
    Move(Piece* movedPiece, pair<int, int> startPos, pair<int,int> endPos, Piece* capturedPiece, bool isCastleK, bool isCastleQ, bool isPromoting, char promoteTo, bool isEP);
    Move(); //DUMMY REMOVE THIS PIECE OF SHIT LATER
    Piece * getMovedPiece(); 
    pair<int, int> getStartPos(); 
    pair<int, int> getEndPos(); 
    Piece* getCapturedPiece(); 
    bool getIsEP();
    
};

#endif
