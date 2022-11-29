#include <vector>
#include <utility>
#include "Pawn.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Pawn::Pawn(bool white, pair<int, int> position) : Piece{white, 1, position, 'P'}, moved{false} {}

vector<Move> Pawn::generateMoves(){
    vector<Move> rawList = {};
    int x = position.first;
    int y = position.second;
    //are we implementing position checks for Pawn? aight
    // ye i can do it
    if (!hasMoved()) {
        if (white) {
            if(x == 1) rawList.push_back(Move{this, make_pair(x + 2, y)}); 
            rawList.push_back(Move{this, make_pair(x + 2, y)});
            rawList.push_back(Move{this, make_pair(x + 1, y + 1)});
            rawList.push_back(Move{this, make_pair(x - 1, y + 1)});
        } else{
            if(x == 6) rawList.push_back(Move{this, make_pair(x - 2, y)}); // wait wtf can u see terminal? come to room
            rawList.push_back(Move{this, make_pair(x - 1, y)});
            rawList.push_back(Move{this, make_pair(x + 1, y - 1)});
            rawList.push_back(Move{this, make_pair(x - 1, y - 1)});
        } 
    }

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

bool Pawn::hasMoved(){
    return moved;
}
