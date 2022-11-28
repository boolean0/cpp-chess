#include <vector>
#include <utility>
#include "King.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

King::King(bool white, pair<int, int> position) : Piece{white, 0, position, 'K'}, moved{false} {}

vector<Move> King::generateMoves(){
    vector<Move> moveList = {};
    return moveList;
}

bool King::hasMoved(){
    return moved;
}
