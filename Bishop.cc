#include <vector>
#include <utility>
#include "Bishop.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Bishop::Bishop(bool white, pair<int, int> position) : Piece{white, 3, position, 'B'} {}

vector<Move> Bishop::generateMoves(){
    vector<Move> rawList = {};
    int row = position.first;
    int col = position.second;
    for(int i = 1; i < 8; i++){
        rawList.push_back(Move{this, make_pair(row+i, col+i)});
        rawList.push_back(Move{this, make_pair(row+i, col-i)});
        rawList.push_back(Move{this, make_pair(row-i, col+i)});
        rawList.push_back(Move{this, make_pair(row-i, col-i)});
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


