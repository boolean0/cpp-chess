#include <vector>
#include <utility>
#include "Bishop.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Bishop::Bishop(bool white, pair<int, int> position) : Piece{white, 3, position, 'B'} {}

vector<Move> Bishop::generateMoves(){
    vector<Move> moveList = {};
    return moveList;
}


