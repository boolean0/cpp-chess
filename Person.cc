#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "Person.h"
#include "ChessBoard.h"

using namespace std;

Person::Person(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    Player{color, inCheck, hasCastled, isComputer, board} {}

Move Person::parseMoveInput() {
    string start,end;
    int x1,x2,y1,y2;
    cin >> start >> end;

    x1 = start[0] - 'a'; 
    y1 = start[1] - '1';
    x2 = end[0] - 'a';
    y2 = end[1] - '1';

    if (!(x1 >= 0 && x1 < 8)) throw invalid_argument("received invalid input");
    if (!(y1 >= 0 && y1 < 8)) throw invalid_argument("received invalid input");
    if (!(x2 >= 0 && x2 < 8)) throw invalid_argument("received invalid input");
    if (!(y2 >= 0 && y2 < 8)) throw invalid_argument("received invalid input");

    pair<int,int> starting = make_pair(x1,y1);
    pair<int,int> ending = make_pair(x2,y2); 

    ChessBoard *board = getBoard();
    
    Move playerMove{board->getPiece(starting), ending,
        board->getPiece(ending) != nullptr 
            ? board->getPiece(ending) 
            : nullptr};
    
    return playerMove;
}

Move Person::handleMove() {
    return parseMoveInput();    
}

