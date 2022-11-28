#ifndef _BISHOP_H_
#define _BISHOP_H_
#include <vector>
#include <utility>
#include "Piece.h"
#include "Move.h"

using namespace std;

class Bishop : public Piece{
    public:
        Bishop(bool isWhite, pair<int, int> position);
        vector<Move> generateMoves() override;
};

#endif