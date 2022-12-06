#include <vector>
#include <utility>
#include "King.h"
#include "Move.h"
#include "Piece.h"

using namespace std;

King::King(bool white, pair<int, int> position) : Piece{white, 5000, position, 'K'} {}

vector<Move> King::generateMoves(){
    vector<Move> rawList = {};
    int row = position.first;
    int col = position.second;
    rawList.push_back(Move{this, position, make_pair(row+1, col)});
    rawList.push_back(Move{this, position, make_pair(row-1, col)});
    rawList.push_back(Move{this, position, make_pair(row, col+1)});
    rawList.push_back(Move{this, position, make_pair(row, col-1)});
    rawList.push_back(Move{this, position, make_pair(row+1, col+1)});
    rawList.push_back(Move{this, position, make_pair(row+1, col-1)});
    rawList.push_back(Move{this, position, make_pair(row-1, col+1)});
    rawList.push_back(Move{this, position, make_pair(row-1, col-1)});

    // potential to castle if hasn't moved yet and is on e1/e8 for white/black kings, respectively
    if (isWhite() && row == 0 && col == 4 && !hasMoved()) {
        rawList.push_back(Move{this, position, make_pair(row, col + 2)});
        rawList.push_back(Move{this, position, make_pair(row, col - 2)});
    }
    else if (!isWhite() && row == 7 && col == 4 && !hasMoved()) {
        rawList.push_back(Move{this, position, make_pair(row, col + 2)});
        rawList.push_back(Move{this, position, make_pair(row, col - 2)});
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

