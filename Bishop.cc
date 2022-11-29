#include <vector>
#include <utility>
#include "Bishop.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Bishop::Bishop(bool white, pair<int, int> position) : Piece{white, 3, position, 'B'} {}

vector<Move> Bishop::generateMoves(){
    vector<Move> rawList = {};
    int x = position.first;
    int y = position.second;
    for(int i = 1; i < 8; i++){
        rawList.push_back(Move{this, make_pair(x+i, y+i)});
        rawList.push_back(Move{this, make_pair(x+i, y-i)});
        rawList.push_back(Move{this, make_pair(x-i, y+i)});
        rawList.push_back(Move{this, make_pair(x-i, y-i)});
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


