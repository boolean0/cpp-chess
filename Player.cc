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

Move Player::castleMoveCreator(Move move) {
    // 0 is no castle, 1 is KS, 2 is QS
    ChessBoard *board = getBoard();
    int type = 0;
    if (getColor() == 1) { //e1 g1 OR e1 c1
        if (move.getStartPos() == make_pair(0, 4)) {
            if(move.getEndPos() == make_pair(0, 6)) type = 1;  // todo make into enum
            else if (move.getEndPos() == make_pair(0, 2)) type = 2;
        }        
    }
    else { // black castling; e8 g8 OR e8 c8
        if (move.getStartPos() == make_pair(7, 4)) {
            if(move.getEndPos() == make_pair(7, 6)) type = 1;  
            else if (move.getEndPos() == make_pair(7, 2)) type = 2;
        } 
    }

    if (type == 1) { // ks castle
        Move m{board->getPiece(move.getStartPos()), move.getStartPos(), move.getEndPos(),
                board->getPiece(move.getEndPos()) != nullptr 
                ? board->getPiece(move.getEndPos()) 
                : nullptr, true, false, false, ' ', false};
        return m;
    }
    else if (type == 2) { // qs castle
        Move m{board->getPiece(move.getStartPos()), move.getStartPos(), move.getEndPos(),
                board->getPiece(move.getEndPos()) != nullptr 
                ? board->getPiece(move.getEndPos()) 
                : nullptr, false, true, false, ' ', false};
        return m;
    }
    else { // no castle
        return move; 
    }
}

bool Player::isCheckmate() { 
    if(getInCheck()){
        
        for(int i = 0; i < 8; i++){
            for(int j = 0; j < 8; j++){
                Piece *p = board->getPiece({i,j});
                if(board->isOccupied({i, j}) && p->isWhite() == color){
                    //check all pieces of same color as player for valid moves, if exists, return false. Else, return true.
                    vector<Move> ml = p->generateMoves(); //these moves do not pass in captured pieces
                    for(Move m : ml){
                        if(board->isOccupied(m.getEndPos())){
                            m = {p, m.getStartPos(), m.getEndPos(), board->getPiece(m.getEndPos())};
                        }
                        try{
                            if(board->checkMoveLegal(m)){ //ERROR HERE
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
                        if(board->isOccupied(m.getEndPos())){
                            m = {p, m.getStartPos(), m.getEndPos(), board->getPiece(m.getEndPos())};
                        }
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
