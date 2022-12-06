#include <vector>
#include <utility>
#include "Knight.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Knight::Knight(bool white, pair<int, int> position) : Piece{white, 30, position, 'N'} {}

vector<Move> Knight::generateMoves(){
    vector<Move> rawList = {};
    int row = position.first;
    int col = position.second;
    rawList.push_back(Move{this, position, make_pair(row+2, col+1)});
    rawList.push_back(Move{this, position, make_pair(row+2, col-1)});
    rawList.push_back(Move{this, position, make_pair(row-2, col+1)});
    rawList.push_back(Move{this, position, make_pair(row-2, col-1)});
    rawList.push_back(Move{this, position, make_pair(row+1, col+2)});
    rawList.push_back(Move{this, position, make_pair(row+1, col-2)});
    rawList.push_back(Move{this, position, make_pair(row-1, col+2)});
    rawList.push_back(Move{this, position, make_pair(row-1, col-2)});

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
