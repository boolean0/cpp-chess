#include <vector>
#include <utility>
#include "Pawn.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

Pawn::Pawn(bool white, pair<int, int> position) : Piece{white, 1, position, 'P'} {}

vector<Move> Pawn::generateMoves(){
    vector<Move> rawList = {};
    int row = position.first;
    int col = position.second;
      if (white) {
        if(row == 1 && !hasMoved()) rawList.push_back(Move{this, make_pair(row + 2, col)}); 
        rawList.push_back(Move{this, make_pair(row + 1, col)});
        rawList.push_back(Move{this, make_pair(row + 1, col + 1)});
        rawList.push_back(Move{this, make_pair(row + 1, col - 1)});
      } else{
        if(row == 6 && !hasMoved()) rawList.push_back(Move{this, make_pair(row - 2, col)});
        rawList.push_back(Move{this, make_pair(row - 1, col)});
        rawList.push_back(Move{this, make_pair(row - 1, col + 1)});
        rawList.push_back(Move{this, make_pair(row - 1, col - 1)});
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
