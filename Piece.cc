#include <utility> 
#include "Piece.h"
#include "Move.h"
#include <vector>
using namespace std; 

Piece::Piece(bool white, int points, pair<int, int> position, char pieceSymbol) 
: white{white}, points{points}, position{position}, pieceSymbol{pieceSymbol}, moved{false} {}

bool Piece::isWhite(){
    return white;
}

int Piece::getPoints(){
    return points;
}

char Piece::getPieceSymbol(){
    return pieceSymbol;
}


pair<int, int> Piece::getPosition(){
    return position;
}

void Piece::setPosition(pair<int, int> pos){
    position = pos;
}

bool Piece::hasMoved() { return moved; }

void Piece::setMoved(bool moved) { this->moved = moved; }

Piece::~Piece() {}
