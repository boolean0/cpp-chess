#ifndef _ROOK_H_
#define _ROOK_H_
#include <vector>
#include <utility>
#include "Piece.h"
#include "Move.h"

using namespace std;

class Rook : public Piece {
    public:
        Rook(bool isWhite, pair<int, int> position);
        vector<Move> generateMoves() override;
};

#endif
