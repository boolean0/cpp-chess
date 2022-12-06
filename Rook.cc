#include <vector>
#include <utility>
#include "Rook.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Rook::Rook(bool white, pair<int, int> position) : Piece{white, 50, position, 'R'} {}

vector<Move> Rook::generateMoves(){
    vector<Move> rawList = {};
    int row = position.first;
    int col = position.second;
    for(int i = 1; i < 8; i++){
        rawList.push_back(Move{this, position, make_pair(row+i, col)});
        rawList.push_back(Move{this, position, make_pair(row-i, col)});
        rawList.push_back(Move{this, position, make_pair(row, col+i)});
        rawList.push_back(Move{this, position, make_pair(row, col-i)});
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

