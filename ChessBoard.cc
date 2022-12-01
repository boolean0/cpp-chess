#include "ChessBoard.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
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

ChessBoard::~ChessBoard() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            delete board[i][j];
        }
    }
}

bool ChessBoard::isPathClear(Move move) { // setup exceptions? 
    int rowDiff = move.getEndPos().first - move.getMovedPiece()->getPosition().first;
    int colDiff = move.getEndPos().second - move.getMovedPiece()->getPosition().second;
    pair<int, int> curPos = move.getMovedPiece()->getPosition();

    if(isOccupied(move.getEndPos()) && // todo do black
    (getPiece(move.getEndPos())->isWhite() == move.getMovedPiece()->isWhite())){
        throw invalid_argument("Cannot move to a square occupied by your own piece!");
        return false;
    }

    if(move.getMovedPiece()->getPieceSymbol() == 'N'){
        return true;
    }

    if(move.getMovedPiece()->getPieceSymbol()=='P'){
        if(colDiff==0 && isOccupied(move.getEndPos())){
            throw invalid_argument("Pawns cannot capture forward!");
            return false;
        }
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
            throw invalid_argument("Cannot move through a piece!");
            return false;
        }
    }
    return true;
}

void ChessBoard::printCLI() {
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

bool ChessBoard::isInCheck(bool white){
    pair<int, int> kingPos;
    //loop through every piece to find right colored-king
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(isOccupied(make_pair(i, j))){
                if((getPiece(make_pair(i, j))->getPieceSymbol() == 'K') && (getPiece(make_pair(i, j))->isWhite() == white)){
                    kingPos = make_pair(i, j);
                }
            }
        }
    } // requires board to have king of each color. If no king, then kingPos defaults to 0 0
    //loop through each piece and check moves to see if kingPos is one of them
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pair<int, int> curSqr = make_pair(i, j);
            if(isOccupied(curSqr) && (getPiece(kingPos)->isWhite() != getPiece(curSqr)->isWhite())){
                vector<Move> ml = getPiece(curSqr)->generateMoves();
                for(Move m : ml){
                    try{
                        if(isPathClear(m) && m.getEndPos() == kingPos){
                            return true;
                        }
                    } catch(invalid_argument& e){
                        //do nothing
                    }
                }
            }
        }
    }

    return false;
}

void ChessBoard::trySetPiece(Move move) {
    // makes the move without destroying the pointer of any piece that was taken so that
    // it can be reinstated at the end

    int rowEnd = move.getEndPos().first;
    int colEnd = move.getEndPos().second;
    int rowStart = move.getStartPos().first; 
    int colStart = move.getStartPos().second;
    board[rowEnd][colEnd] = move.getMovedPiece();
    board[rowStart][colStart] = nullptr; 

}

void ChessBoard::resetMove(Move move) {
    int rowEnd = move.getEndPos().first;
    int colEnd = move.getEndPos().second;
    int rowStart = move.getStartPos().first; 
    int colStart = move.getStartPos().second;
    board[rowEnd][colEnd] = move.getCapturedPiece();
    board[rowStart][colStart] = move.getMovedPiece();
}

bool ChessBoard::simulateMove(Move move) { 
    // simulates making the move; checks if after the move, you're in check, which 
    // makes the move invalid because the opponent can capture your king
    // does NOT change the state of the board after simulateMove finishes
    if (move.getMovedPiece()->getPieceSymbol() == 'P') {
        int colDiff = move.getEndPos().second - move.getStartPos().second;
        if (colDiff != 0 && move.getCapturedPiece() == nullptr) {
            throw invalid_argument("Pawn cannot move diagonally if there is no piece to capture!");
            return false;
        }
    }
    trySetPiece(move); 
    bool colour = move.getMovedPiece()->isWhite();
    bool ret = true; 
    if (isInCheck(colour)) {
        resetMove(move);
        throw invalid_argument("Cannot make that move because it would put you in check, or you are already in check!");
        ret = false;
    }
    
    resetMove(move); 
    return ret;
}

void ChessBoard::afterMove(Move move) {
    Piece * p = move.getMovedPiece();
    p->setMoved(true);  
   /* if(p->getPieceSymbol() == 'P'){
        int rowDiff = move.getEndPos().first - move.getStartPos().first;
        if(rowDiff == 2 || rowDiff == -2){
            p->setEnPassant(true);
        }
    } */

    if(p->getPieceSymbol() == 'P' && (move.getEndPos().first == 0 || move.getEndPos().first == 7)){
        //pawn promotion
        char newPiece;
        cout << "Enter the piece you want to promote to (Q, R, B, N): ";
        while(cin >> newPiece){
            if(newPiece == 'Q'){
                board[move.getEndPos().first][move.getEndPos().second] = new Queen(p->isWhite(), move.getEndPos());
                break;
            } else if(newPiece == 'R'){
                board[move.getEndPos().first][move.getEndPos().second] = new Rook(p->isWhite(), move.getEndPos());
                break;
            } else if(newPiece == 'B'){
                board[move.getEndPos().first][move.getEndPos().second] = new Bishop(p->isWhite(), move.getEndPos());
                break;
            } else if(newPiece == 'N'){
                board[move.getEndPos().first][move.getEndPos().second] = new Knight(p->isWhite(), move.getEndPos());
                break;
            } else{
                cout << "Invalid piece. Try again." << endl;
                continue;
            }
        }
        delete p;
    }
}

void ChessBoard::doMove(Move move) { 
    // THIS ASSUMES THE MOVE IS VALID AND LEGAL
    // ONLY CALL AFTER ALL CHECKS ON MOVES HAVE BEEN DONE!

    setPiece(move.getEndPos(), move.getMovedPiece());
    cout << "Moved " << move.getMovedPiece()->getPieceSymbol() << " from (" <<
                move.getStartPos().first << ", " << move.getStartPos().second
                << ") to (" << move.getEndPos().first 
                << "," << move.getEndPos().second << ")" << endl;
    setPiece(move.getStartPos(), nullptr);
    move.getMovedPiece()->setPosition(move.getEndPos());

    afterMove(move);
}



Piece* ChessBoard::getPiece(pair<int, int> square) {
    return board[square.first][square.second];
}

void ChessBoard::setPiece(pair<int,int> square, Piece* piece) {
    //delete board[square.first][square.second];
    board[square.first][square.second] = piece;
}

bool ChessBoard::checkInDanger() {
    return false;
}

bool ChessBoard::isOccupied(pair<int,int> square) {
    return !(board[square.first][square.second] == nullptr);
}

bool ChessBoard::isPotentialMove(Move move) {
    // checks if a piece could potentially move to the square given its move patterns
    Piece * movingPiece = move.getMovedPiece(); 
    vector<Move> moveList = movingPiece->generateMoves();

    for (int i = 0; i < (int)moveList.size(); ++i) {
        if (moveList[i].getEndPos() == move.getEndPos()) return true;
    }
    throw invalid_argument("Not a move that piece can make!");
    return false;
}

bool ChessBoard::checkMoveLegal(Move move) {
    return isPotentialMove(move) && isPathClear(move) && simulateMove(move);
}
