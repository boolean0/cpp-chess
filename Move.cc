#include <utility>
#include "Move.h"

using namespace std;

Move::Move(Piece* movedPiece, pair<int,int> endPos, Piece* capturedPiece) : // for regular moves
    movedPiece{movedPiece}, 
    endPos{endPos}, 
    capturedPiece{capturedPiece},
    isCastleK{false},
    isCastleQ{false},
    isPromoting{false},
    isEP{false}{}

Move::Move(Piece* movedPiece, pair<int, int> endPos, Piece* capturedPiece, bool isCastleK, bool isCastleQ, bool isPromoting, char promoteTo, bool isEP) :
    movedPiece{movedPiece},
    endPos{endPos}, 
    capturedPiece{capturedPiece},
    isCastleK{isCastleK},
    isCastleQ{isCastleQ},
    isPromoting{isPromoting},
    isEP{isEP} {}


//REMOVE ME IM USELESS
Move::Move() : 
    movedPiece{nullptr}, 
    endPos{make_pair(0,0)}, 
    capturedPiece{nullptr},
    isCastleK{false},
    isCastleQ{false},
    isPromoting{false},
    isEP{false}{}

Piece* Move::getMovedPiece(){
    return movedPiece;
}

pair<int, int> Move::getStartPos(){
    return movedPiece->getPosition();
}

pair<int, int> Move::getEndPos(){
    return endPos;
}

Piece* Move::getCapturedPiece(){
    return capturedPiece;
}

bool Move::isPotentialKSCastle() { return isCastleK; }

bool Move::isPotentialQSCastle() { return isCastleQ; }
