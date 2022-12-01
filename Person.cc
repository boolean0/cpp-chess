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
    //getBoard()->printCLI(); 
    col1 = start[0] - 'a'; 
    row1 = start[1] - '1';
    col2 = end[0] - 'a';
    row2 = end[1] - '1';

    if (!(row1 >= 0 && row1 < 8)) throw invalid_argument("received invalid input");
    if (!(col1 >= 0 && col1 < 8)) throw invalid_argument("received invalid input");
    if (!(row2 >= 0 && row2 < 8)) throw invalid_argument("received invalid input");
    if (!(col2 >= 0 && col2 < 8)) throw invalid_argument("received invalid input");

    pair<int,int> starting = make_pair(row1, col1);
    pair<int,int> ending = make_pair(row2, col2); 
    ChessBoard *board = getBoard();
    // checking if there is a piece to move
    if (!board->isOccupied(starting)) {
        throw invalid_argument("No piece to move at that square!");
    }
    // checking if there is a piece of the right colour to move
    else if(board->isOccupied(starting) && (board->getPiece(starting)->isWhite() != getColor())) {
        string color = getColor() ? "white" : "black";
        string arg = "No " + color + " piece to move at that square!";
        throw invalid_argument(arg);
    }
    Move playerMove{board->getPiece(starting), ending,
        board->getPiece(ending) != nullptr 
            ? board->getPiece(ending) 
            : nullptr};
    
    //enpassant
    // if(board->getPiece(starting)->getPieceSymbol()=='P'){ // is moving piece a pawn?
    //     if(ending.second==2 && board->getPiece(starting)->isWhite()){ // is pawn moving to row 2
    //         if(board->getPiece(make_pair(playerMove.getEndPos().first,3))!=nullptr){
    //             if(board->getPiece(make_pair(playerMove.getEndPos().first,3))->getPieceSymbol()=='P'){
    //                 if(board->getPiece(make_pair(playerMove.getEndPos().first,3))->getEnPassant()){
    //                     playerMove.setEnPassant(true);
    //                 }
    //             }
    //         }
    //     }
    // }


    return playerMove;
}

Move Person::handleMove() {
    return parseMoveInput();    
}

