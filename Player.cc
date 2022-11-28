#include "Player.h"

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
    //TODO!
    return 0;
}

bool Player::isStalemate() {
    //TODO!
    return 0;
}
