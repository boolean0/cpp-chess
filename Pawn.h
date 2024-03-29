#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include <utility>
#include "Piece.h"
#include "Move.h"

using namespace std;

class Pawn : public Piece{
    bool enPassant;
    public:
        Pawn(bool isWhite, pair<int, int> position);
        vector<Move> generateMoves() override;
        void setEnPassant(bool enPassant);
        bool getEnPassant();
        
};

#endif
