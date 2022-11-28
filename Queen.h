#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <vector>
#include <utility>
#include "Piece.h"
#include "Move.h"

using namespace std;

class Queen : public Piece{
    public:
        Queen(bool isWhite, pair<int, int> position);
        vector<Move> generateMoves() override;
};

#endif
