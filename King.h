#ifndef _KING_H_
#define _KING_H_
#include <vector>
#include <utility>
#include "Piece.h"
#include "Move.h"

using namespace std;

class King : public Piece{
    private: 
        bool moved;
    public:
        King(bool isWhite, pair<int, int> position);
        vector<Move> generateMoves() override;
        bool hasMoved();
};

#endif