#include <vector>
#include <utility>
#include "Pawn.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Pawn::Pawn(bool white, pair<int, int> position) : Piece{white, 1, position, 'P'}, moved{false} {}

vector<Move> Pawn::generateMoves(){
    vector<Move> moveList = {};
    return moveList;
}

bool Pawn::hasMoved(){
    return moved;
}
