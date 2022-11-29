#include "ChessBoard.h"
#include "Piece.h"
#include <iostream>
#include <utility>
#include <vector>

using namespace std;

void ChessBoard::init() { // init board to all blank
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}

bool ChessBoard::isPathClear(Move move) {
    int rowDiff = move.getEndPos().first - move.getMovedPiece()->getPosition().first;
    int colDiff = move.getEndPos().second - move.getMovedPiece()->getPosition().second;
    pair<int, int> curPos = move.getMovedPiece()->getPosition();

    if(isOccupied(move.getEndPos()) && 
    (getPiece(move.getEndPos())->isWhite() && move.getMovedPiece()->isWhite())){
        //check if endPos has a piece and if they are same color, return false
        return false;
    }

    if(move.getMovedPiece()->getPieceSymbol() == 'N'){
        return true;
    }

    while(curPos != move.getEndPos()){
        if(rowDiff > 0 && colDiff == 0){ //Piece is moving up (e.g. A1 -> A3)
            curPos.first++;
        } else if (rowDiff < 0 && colDiff == 0){ //Piece is moving down (e.g. A3 -> A1)
            curPos.first--;
        } else if(rowDiff == 0 && colDiff > 0){ //Piece is moving right (e.g. A1 -> C1)
            curPos.second++;
        } else if(rowDiff == 0 && colDiff < 0){ //Piece is moving left (e.g. C1 -> A1)
            curPos.second--;
        } else if(rowDiff > 0 && colDiff > 0){ //Piece is moving up-right (e.g. A1 -> C3)
            curPos.first++;
            curPos.second++;
        } else if(rowDiff > 0 && colDiff < 0){ //Piece is moving up-left (e.g. C1 -> A3)
            curPos.first++;
            curPos.second--;
        } else if(rowDiff < 0 && colDiff > 0){ //Piece is moving down-right (e.g. A3 -> C1)
            curPos.first--;
            curPos.second++;
        } else if(rowDiff < 0 && colDiff < 0){ //Piece is moving down-left (e.g. C3 -> A1)
            curPos.first--;
            curPos.second--;
        }
        if(isOccupied(curPos) && curPos != move.getEndPos()){
            return false;
        }
    }
    return true;
}

bool ChessBoard::isInCheck(bool white){
    pair<int, int> kingPos;
    //loop through every piece to find right colored-king
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(isOccupied(make_pair(i, j))){
                if((getPiece(make_pair(i, j))->getPieceSymbol() == 'K') && (getPiece(make_pair(i, j))->isWhite() && white)){
                    kingPos = make_pair(i, j);
                }
            }
        }
    } // requires board to have king of each color. If no king, then kingPos defaults to 0 0
    //loop through each piece and check moves to see if kingPos is one of them
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(isOccupied(make_pair(i, j))){
                vector<Move> ml = getPiece(make_pair(i, j))->generateMoves();
                for(Move m : ml){
                    if(isPathClear(m) && m.getEndPos() == kingPos){
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

bool ChessBoard::simulateMove(Move move) { return true; }

Piece* ChessBoard::getPiece(pair<int, int> square) {
    return board[square.first][square.second];
}

void ChessBoard::setPiece(pair<int,int> square, Piece* piece) {
    delete board[square.first][square.second];
    board[square.first][square.second] = piece;
}

bool ChessBoard::checkInDanger() {
    return false;
}

bool ChessBoard::isOccupied(pair<int,int> square) {
    return !(board[square.first][square.second] == nullptr);
}

bool ChessBoard::checkMoveLegal(Move move) {
    return true;
}

void ChessBoard::printCLI(){
    for(int i = 7; i >= 0; --i){ //starts from a8 (0,0)
        for(int j = 0; j < 8; j++){
            if(isOccupied(make_pair(i, j))){
                Piece* piece = getPiece(make_pair(i, j));
                if(piece->isWhite()){
                    cout << piece->getPieceSymbol();
                } else {
                    char lower = tolower(piece->getPieceSymbol());
                    cout << lower;
                }
            } else {
                //check for white or black square
                if((i+j)%2 == 0){
                    cout << ' ';
                } else{
                    cout << '_';
                }
            }
        }
        cout << endl;
    }
}

