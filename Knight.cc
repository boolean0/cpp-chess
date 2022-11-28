#include <vector>
#include <utility>
#include "Knight.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Knight::Knight(bool white, pair<int, int> position) : Piece{white, 3, position, 'N'} {}

vector<Move> Knight::generateMoves(){
    vector<Move> moveList = {};
    return moveList;
}