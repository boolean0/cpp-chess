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
    // TODO: CHECK FOR PAWN PROMOTION, CASTLING!
    string start,end;
    int row1, row2, col1, col2;
    cin >> start >> end;

    row1 = start[0] - 'a'; 
    col1 = start[1] - '1';
    row2 = end[0] - 'a';
    col2 = end[1] - '1';

    if (!(row1 >= 0 && row1 < 8)) throw invalid_argument("received invalid input");
    if (!(col1 >= 0 && col1 < 8)) throw invalid_argument("received invalid input");
    if (!(row2 >= 0 && row2 < 8)) throw invalid_argument("received invalid input");
    if (!(col2 >= 0 && col2 < 8)) throw invalid_argument("received invalid input");

    pair<int,int> starting = make_pair(row1,col1);
    pair<int,int> ending = make_pair(row2,col2); 

    ChessBoard *board = getBoard();
    
    // checking if there is a piece to move
    if (!board->isOccupied(starting)) {
        throw invalid_argument("No piece to move at that square!");
    }
    Move playerMove{board->getPiece(starting), ending,
        board->getPiece(ending) != nullptr 
            ? board->getPiece(ending) 
            : nullptr};
    
    return playerMove;
}

Move Person::handleMove() {
    return parseMoveInput();    
}

