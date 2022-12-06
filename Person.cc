#include <iostream>
#include <string>
#include <utility>
#include <stdexcept>
#include "Person.h"
#include "ChessBoard.h"
#include "Pawn.h"

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

    Move playerMove{board->getPiece(starting), starting, ending,
        board->getPiece(ending) != nullptr 
            ? board->getPiece(ending) 
            : nullptr};
    
    if (playerMove.getMovedPiece()->getPieceSymbol() == 'K' && !playerMove.getMovedPiece()->hasMoved()) {
        // king moved check is just for performance; don't want to go through the function if we know the king's already moved; 
        // this is not a comprehensive check, we will still prune the move later in checkmovelegal
        Move ret = castleMoveCreator(playerMove); // will convert move into a castling move if it is castling
        return ret;
    }

    if(board->getPiece(starting)->getPieceSymbol()=='P'){ // is moving piece a pawn?
        if(ending.first==5 && board->getPiece(starting)->isWhite()){ // is it a white pawn moving to row 5 ?   
            if(board->isOccupied(make_pair(4, ending.second)) 
            && board->getPiece(make_pair(4,ending.second))->getPieceSymbol() == 'P'
            && !board->getPiece(make_pair(4, ending.second))->isWhite()){ // is there a black pawn in the enpassant square?
                Pawn *p = dynamic_cast<Pawn*>(board->getPiece(make_pair(4, ending.second)));
                if(p->getEnPassant()){ // is the black pawn in the enpassant square eligible for enpassant?
                    Move enPassantMove{board->getPiece(starting), starting, ending, p, false, false, false, '\0', true};
                    return enPassantMove;
                }
            }
        } else if(ending.first==2 && !board->getPiece(starting)->isWhite()){ // is it a black pawn moving to row 5 ?   
            if(board->isOccupied(make_pair(3, ending.second)) 
            && board->getPiece(make_pair(3,ending.second))->getPieceSymbol() == 'P'
            && board->getPiece(make_pair(3, ending.second))->isWhite()){ // is there a white pawn in the enpassant square?
                Pawn *p = dynamic_cast<Pawn*>(board->getPiece(make_pair(3, ending.second)));
                if(p->getEnPassant()){ // is the white pawn in the enpassant square eligible for enpassant?
                    Move enPassantMove{board->getPiece(starting), starting, ending, p, false, false, false, '\0', true};
                    return enPassantMove;
                }
            }
        }
    }

    return playerMove;
}

Move Person::handleMove() {
    return parseMoveInput();    
}

