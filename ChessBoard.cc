#include "ChessBoard.h"
#include "Piece.h"
#include <iostream>
#include <utility>

using namespace std;

void ChessBoard::init() { // init board to all blank
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            board[i][j] = nullptr;
        }
    }
}

bool ChessBoard::isPathClear(Move move) {
    return true;
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

