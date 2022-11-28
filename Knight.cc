#include <vector>
#include <utility>
#include "Knight.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Knight::Knight(bool white, pair<int, int> position) : Piece{white, 3, position, 'N'} {}

vector<Move> Knight::generateMoves(){
    vector<Move> rawList = {};
    int x = position.first;
    int y = position.second;
    rawList.push_back(Move{this, make_pair(x+2, y+1)});
    rawList.push_back(Move{this, make_pair(x+2, y-1)});
    rawList.push_back(Move{this, make_pair(x-2, y+1)});
    rawList.push_back(Move{this, make_pair(x-2, y-1)});
    rawList.push_back(Move{this, make_pair(x+1, y+2)});
    rawList.push_back(Move{this, make_pair(x+1, y-2)});
    rawList.push_back(Move{this, make_pair(x-1, y+2)});
    rawList.push_back(Move{this, make_pair(x-1, y-2)});

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
