#include "ChessBoard.h"
#include "Piece.h"
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

    if (isOccupied(move.getEndPos())) {
        cout << "Pieces on end squares:" << endl;
        cout << getPiece(move.getEndPos())->getPieceSymbol() << " " 
        << getPiece(move.getEndPos())->isWhite() << endl;
    }
    
    
    if(isOccupied(move.getEndPos()) && // todo do black
    (getPiece(move.getEndPos())->isWhite() == move.getMovedPiece()->isWhite())){
        //check if endPos has a piece and if they are same color, return false
        cerr << "Path is blocked!" << endl;
        return false;
    }

    if(move.getMovedPiece()->getPieceSymbol() == 'N'){
        return true;
    }

    if(move.getMovedPiece()->getPieceSymbol()=='P'){
        if(colDiff==0 && isOccupied(move.getEndPos())){
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
            cerr << "Cannot make that move because the path is blocked!" << endl;
            cerr << move.getEndPos().first << " " << move.getEndPos().second << endl;
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
                if((getPiece(make_pair(i, j))->getPieceSymbol() == 'K') && (getPiece(make_pair(i, j))->isWhite() && white)){
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
                cout << getPiece(curSqr)->getPieceSymbol() << " " << getPiece(curSqr)->isWhite() << endl;
                vector<Move> ml = getPiece(curSqr)->generateMoves();
                for(Move m : ml){
                    if(isPathClear(m) && m.getEndPos() == kingPos){
                        return true;
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
    trySetPiece(move); 

    //testing
    cout << "simulated board: " << endl;
    notifyObservers();
    ////////////////


    bool colour = move.getMovedPiece()->isWhite();
    bool ret = true; 
    if (isInCheck(colour)) {
        cerr << "Cannot make that move because it would put you in check, or you are already in check!" << endl;
        ret = false;
    }
    
    resetMove(move); 
    return ret;
}



void ChessBoard::doMove(Move move) { 
    // THIS ASSUMES THE MOVE IS VALID AND LEGAL
    // ONLY CALL AFTER ALL CHECKS ON MOVES HAVE BEEN DONE!
    setPiece(move.getEndPos(), move.getMovedPiece());
    cout << "Moved " << move.getMovedPiece()->getPieceSymbol() << " from " <<
                move.getStartPos().first << ", " << move.getStartPos().second
                << " to " << move.getEndPos().first 
                << ", " << move.getEndPos().second << endl;
    setPiece(move.getStartPos(), nullptr);
    move.getMovedPiece()->setPosition(move.getEndPos());
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
    cerr << "Not a move that piece can make!" << endl;
    return false;
}

bool ChessBoard::checkMoveLegal(Move move) {
    if (isPotentialMove(move)) { //explicit checks
        if (isPathClear(move)) {
            cout << "here: " << endl;
            notifyObservers();
            if (simulateMove(move)) { // breaks here..
                cout << "Reset board: " << endl;
                notifyObservers();
                return true;
            }
        }
    }
    return false;
}
