#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <vector>
#include <utility>
#include "Piece.h"
#include "Move.h"

using namespace std;

class Knight : public Piece {
    public:
        Knight(bool isWhite, pair<int, int> position);
        vector<Move> generateMoves() override;
};

#endif
