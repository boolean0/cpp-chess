#include <vector>
#include <utility>
#include "Pawn.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Pawn::Pawn(bool white, pair<int, int> position) : Piece{white, 1, position, 'P'}, moved{false} {}

vector<Move> Pawn::generateMoves(){
    vector<Move> rawList = {};
    int row = position.first;
    int col = position.second;
    //are we implementing position checks for Pawn? aight
    // cole i can do it
    if (!hasMoved()) {
        if (white) {
            if(row == 1) rawList.push_back(Move{this, make_pair(row + 2, col)}); 
            rawList.push_back(Move{this, make_pair(row + 2, col)});
            rawList.push_back(Move{this, make_pair(row + 1, col + 1)});
            rawList.push_back(Move{this, make_pair(row - 1, col + 1)});
        } else{
            if(row == 6) rawList.push_back(Move{this, make_pair(row - 2, col)}); // wait wtf can u see terminal? come to room
            rawList.push_back(Move{this, make_pair(row - 1, col)});
            rawList.push_back(Move{this, make_pair(row + 1, col - 1)});
            rawList.push_back(Move{this, make_pair(row - 1, col - 1)});
        } 
    }

    vector<Move> moveList = {};
    for(Move move : rawList){
        int row = move.getEndPos().first;
        int col = move.getEndPos().second;
        if(!((row < 0) || (row > 7) || (col < 0) || (col > 7))){
            moveList.push_back(move);
        }
    } 
    return moveList;
}

bool Pawn::hasMoved(){
    return moved;
}
