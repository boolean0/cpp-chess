#include <vector>
#include <utility>
#include "Queen.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Queen::Queen(bool white, pair<int, int> position) : Piece{white, 9, position, 'Q'} {}

vector<Move> Queen::generateMoves(){
    vector<Move> moveList = {};
    return moveList;
}


