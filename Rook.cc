#include <vector>
#include <utility>
#include "Rook.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Rook::Rook(bool white, pair<int, int> position) : Piece{white, 5, position, 'R'}, moved{false} {}

vector<Move> Rook::generateMoves(){
    vector<Move> moveList = {};
    return moveList;
}

bool Rook::hasMoved(){
    return moved;
}


