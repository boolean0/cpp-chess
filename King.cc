#include <vector>
#include <utility>
#include "King.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

King::King(bool white, pair<int, int> position) : Piece{white, 0, position, 'K'}, moved{false} {}

vector<Move> King::generateMoves(){
    vector<Move> rawList = {};
    int x = position.first;
    int y = position.second;
    rawList.push_back(Move{this, make_pair(x+1, y)});
    rawList.push_back(Move{this, make_pair(x-1, y)});
    rawList.push_back(Move{this, make_pair(x, y+1)});
    rawList.push_back(Move{this, make_pair(x, y-1)});
    rawList.push_back(Move{this, make_pair(x+1, y+1)});
    rawList.push_back(Move{this, make_pair(x+1, y-1)});
    rawList.push_back(Move{this, make_pair(x-1, y+1)});
    rawList.push_back(Move{this, make_pair(x-1, y-1)});

    vector<Move> moveList = {};
    for(Move move : rawList){
        int x = move.getEndPos().first;
        int y = move.getEndPos().second;
        if(!((x < 0) || (x > 7) || (y < 0) || (y > 7))){
            moveList.push_back(move);
        }
    } 
    return moveList;
}

bool King::hasMoved(){
    return moved;
}
