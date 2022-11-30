#include "Player.h"
#include <iostream>

Player::Player(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board) :
    color{color}, inCheck{inCheck}, hasCastled{hasCastled}, isComputer{isComputer}, board{board} {}

Player::~Player() {}

void Player::setInCheck(bool inCheck) {
    this->inCheck = inCheck;
}

void Player::setHasCastled(bool hasCastled) {
    this->hasCastled = hasCastled;
}

ChessBoard *Player::getBoard() {
    return board;
}

bool Player::getColor() {
    return color;
}

bool Player::getInCheck() {
    return inCheck;
}

bool Player::getHasCastled() {
    return hasCastled;
}

bool Player::isCheckmate() { 
    if(getInCheck()){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Piece *p = board->getPiece({i,j});
                if(board->isOccupied({i, j}) && p->isWhite() == color){
                    //check all pieces of same color as player for valid moves, if exists, return false. Else, return true.
                    vector<Move> ml = p->generateMoves();
                    for(Move m : ml){
                        try{
                            if(board->checkMoveLegal(m)){
                                return false;
                            }
                        } catch(std::invalid_argument &err){
                            //do nothing
                        }
                    }
                }
            }
        }
        return true;
    }
    //return false if not in check
    return false;
}

bool Player::isStalemate() {
    if(!getInCheck()){
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Piece *p = board->getPiece({i,j});
                if(board->isOccupied({i, j}) && p->isWhite() == color){
                    //check all pieces of same color as player for valid moves, if exists, return false. Else, return true.
                    vector<Move> ml = p->generateMoves();
                    for(Move m : ml){
                        try{
                            if(board->checkMoveLegal(m)){
                                return false;
                            }
                        } catch(std::invalid_argument &err){
                            //do nothing
                        }
                    }
                }
            }
        }
        return true;
    }
    //return false if in check
    return false;
}
