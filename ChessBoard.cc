#include "ChessBoard.h"
#include "Piece.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"
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

    if ( (move.isPotentialKSCastle() || move.isPotentialQSCastle()) && isOccupied(move.getEndPos())) {
        // cannot have anything in the way during castling
        throw invalid_argument("The path between your king and rook cannot be blocked during castling!");
    }

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
    move.getMovedPiece()->setPosition(move.getEndPos());

}

void ChessBoard::resetMove(Move move) {
    int rowEnd = move.getEndPos().first;
    int colEnd = move.getEndPos().second;
    int rowStart = move.getStartPos().first; 
    int colStart = move.getStartPos().second;
    board[rowEnd][colEnd] = move.getCapturedPiece();
    board[rowStart][colStart] = move.getMovedPiece();
    move.getMovedPiece()->setPosition(move.getStartPos());
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
        //return ret;
    }

    resetMove(move);
    return ret;
}

void ChessBoard::afterMove(Move move) {
    cout << "After move: " << endl;
    Piece * p = move.getMovedPiece();
    p->setMoved(true);

    //if pawn was captured, and it was enpassant, remove it from the board
    if(move.getIsEP()){
            pair<int, int> capturedPawnPos = move.getCapturedPiece()->getPosition();
            setPiece(capturedPawnPos, nullptr); //this leaks memory but works
            //delete board[capturedPawnPos.first][capturedPawnPos.second]; //this crashes the program
    }
    //set all pawns enpassant value to false
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            Piece *tmp = getPiece(make_pair(i, j));
            if(tmp != nullptr && tmp->getPieceSymbol() == 'P'){
                dynamic_cast<Pawn *>(tmp)->setEnPassant(false);
            }
        }
    }
    //if pawn was the moved piece, and it just moved two squares, set enpassant to true
    if(p->getPieceSymbol() == 'P'){
        int rowDiff = move.getEndPos().first - move.getStartPos().first;
        pair<int, int> leftOfPos = make_pair(move.getEndPos().first, move.getEndPos().second - 1);
        pair<int, int> rightOfPos = make_pair(move.getEndPos().first, move.getEndPos().second + 1);
        Piece *leftOf = getPiece(leftOfPos);
        Piece *rightOf = getPiece(rightOfPos);
        if((rowDiff == 2 || rowDiff == -2) && ((leftOf != nullptr && leftOf->getPieceSymbol() == 'P') || (rightOf != nullptr && rightOf->getPieceSymbol() == 'P'))){
            dynamic_cast<Pawn *>(p)->setEnPassant(true);
        }
    }
    //pawn promotion
    if(p->getPieceSymbol() == 'P' && (move.getEndPos().first == 0 || move.getEndPos().first == 7)){
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
    if (move.getMovedPiece() == nullptr ) cout << "null " << endl;
    setPiece(move.getEndPos(), move.getMovedPiece());
    cout << "Moved " << move.getMovedPiece()->getPieceSymbol() << " from (" <<
                move.getStartPos().first << ", " << move.getStartPos().second
                << ") to (" << move.getEndPos().first 
                << "," << move.getEndPos().second << ")" << endl;
    setPiece(move.getStartPos(), nullptr);
    move.getMovedPiece()->setPosition(move.getEndPos());
    afterMove(move);

    // if it is castling, we also need to move the rook, just do it here lol
    // we know the castle is valid
    bool pieceColour = move.getMovedPiece()->isWhite();
    if (move.isPotentialKSCastle() && pieceColour) {
        pair<int, int> h1 = make_pair(0, 7);
        pair<int, int> f1 = make_pair(0, 5);
        Move Rf1{getPiece(h1), h1, f1, nullptr}; 
        doMove(Rf1);
    }
    else if (move.isPotentialQSCastle() && pieceColour) {
        pair<int, int> a1 = make_pair(0, 0);
        pair<int, int> d1 = make_pair(0, 3);
        Move Rd1{getPiece(a1), a1, d1, nullptr};
        doMove(Rd1);
    }
    else if (move.isPotentialKSCastle() && !pieceColour) {
        pair<int, int> h8 = make_pair(7, 7);
        pair<int, int> f8 = make_pair(7, 5); 
        Move Rf8{getPiece(h8), h8, f8, nullptr};
        doMove(Rf8);
    }
    else if (move.isPotentialQSCastle() && !pieceColour) {
        pair<int, int> a8 = make_pair(7, 0); 
        pair<int, int> d8 = make_pair(7, 3); 
        Move Rd8{getPiece(a8), a8, d8, nullptr};
        doMove(Rd8);
    }
}



Piece* ChessBoard::getPiece(pair<int, int> square) {
    return board[square.first][square.second];
}

void ChessBoard::setPiece(pair<int,int> square, Piece* piece) {
    //delete board[square.first][square.second];
    board[square.first][square.second] = piece;
}

bool ChessBoard::checkInDanger(Piece * piece) { // for AI
    pair<int, int> piecePos = piece->getPosition();
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pair<int, int> curSqr = make_pair(i, j);
            if(isOccupied(curSqr) && (getPiece(piecePos)->isWhite() != getPiece(curSqr)->isWhite())){
                vector<Move> ml = getPiece(curSqr)->generateMoves();
                for(Move m : ml){
                    try{
                        if(isPathClear(m) && m.getEndPos() == piecePos) { 
                            // if they can legally take the piece, it's in danger
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

bool ChessBoard::isMovingOutOfDanger(Move move) {
    trySetPiece(move);
    bool ret = false; 
    move.getMovedPiece()->setPosition(move.getEndPos()); // set this because we need to check danger again with updated pos 
    try {
        if (!checkInDanger(move.getMovedPiece())) {
            // if no longer in danger return true
            ret = true;
        }
    }
    catch (invalid_argument& err) {}
    resetMove(move); 
    move.getMovedPiece()->setPosition(move.getStartPos());
    return ret;
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

Move ChessBoard::castlingKingMoveFactory(Move kingMove, pair<int, int> ending, bool isKSCastle) {
    // creates king moves for castle checking
    Move m{kingMove.getMovedPiece(), kingMove.getStartPos(), ending,
     isOccupied(ending) ? getPiece(ending) : nullptr, 
     isKSCastle ? true : false, 
     isKSCastle ? false : true, //queenside opposite of kingside
     false, ' ', false} ; 
     return m;
}

bool ChessBoard::checkLegalCastle(Move move, bool isKSCastle) {
    // assumes castle move

    
    bool clear = false;
    try {
        clear = isPathClear(move); 
        // this will return false if there is a opp coloured piece on the square king will land on during castling
    }
    catch (invalid_argument& err) {
        //cerr << err.what() << endl;
    }
    if (!clear) return false;

    bool colour = move.getMovedPiece()->isWhite();
    if (isInCheck(colour)) return false; // cannot castle out of check, setup exception?

    bool intermediateSquaresClear = false;
    bool notInCheckDuringCastle = false;
    if (colour && isKSCastle) { //white KS castle
        // check if there is a white rook on h1 that hasn't moved 
        pair<int, int> h1 = make_pair(0, 7);
        if (!(isOccupied(h1) && getPiece(h1)->getPieceSymbol() == 'R' && !getPiece(h1)->hasMoved() 
        && getPiece(h1)->isWhite() == colour)) {
            return false;
        }
        // check clear path b/w rook and king
        Move f1 = castlingKingMoveFactory(move, make_pair(0, 5), isKSCastle);
        Move g1 = castlingKingMoveFactory(move, make_pair(0, 6), isKSCastle);

        intermediateSquaresClear = isPathClear(f1) && isPathClear(g1);
        notInCheckDuringCastle = simulateMove(f1) && simulateMove(g1);
    }
    else if (colour && !isKSCastle) {
        pair<int, int> a1 = make_pair(0, 0); 
        if (!(isOccupied(a1) && getPiece(a1)->getPieceSymbol() == 'R' && !getPiece(a1)->hasMoved()
        && getPiece(a1)->isWhite() == colour)) {
            return false;
        }

        Move Kd1 = castlingKingMoveFactory(move, make_pair(0, 3), isKSCastle);
        Move Kc1 = castlingKingMoveFactory(move, make_pair(0, 2), isKSCastle);
        Move Rad1{getPiece(a1), a1, make_pair(0, 3), getPiece(make_pair(0, 3)) != nullptr ? getPiece(make_pair(0, 3)) : nullptr};

        intermediateSquaresClear = isPathClear(Kd1) && isPathClear(Kc1) && isPathClear(Rad1); // checks if there is a piece on b1
        notInCheckDuringCastle = simulateMove(Kd1) && simulateMove(Kc1); 
    }
    else if (!colour && isKSCastle) {
        pair<int, int> h8 = make_pair(7, 7); 
        if (!(isOccupied(h8) && getPiece(h8)->getPieceSymbol() == 'R' && !getPiece(h8)->hasMoved()
        && getPiece(h8)->isWhite() == colour)) {
            return false;
        }
        // check clear path b/w rook and king
        Move f8 = castlingKingMoveFactory(move, make_pair(7, 5), isKSCastle);
        Move g8 = castlingKingMoveFactory(move, make_pair(7, 6), isKSCastle);

        intermediateSquaresClear = isPathClear(f8) && isPathClear(g8);
        notInCheckDuringCastle = simulateMove(f8) && simulateMove(g8);
    }
    else if (!colour && !isKSCastle) {
        pair<int, int> a8 = make_pair(7, 0); 
        if (!(isOccupied(a8) && getPiece(a8)->getPieceSymbol() == 'R' && !getPiece(a8)->hasMoved()
        && getPiece(a8)->isWhite() == colour)) {
            return false;
        }

        Move d8 = castlingKingMoveFactory(move, make_pair(7, 3), isKSCastle);
        Move c8 = castlingKingMoveFactory(move, make_pair(7, 2), isKSCastle);
        Move Rad8{getPiece(a8), a8, make_pair(7, 3), getPiece(make_pair(7, 3)) != nullptr ? getPiece(make_pair(7, 3)) : nullptr};

        intermediateSquaresClear = isPathClear(d8) && isPathClear(c8) && isPathClear(Rad8); // checks if there ia piece on b8
        notInCheckDuringCastle = simulateMove(d8) && simulateMove(c8); 
    }
    return intermediateSquaresClear && notInCheckDuringCastle; 
}

bool ChessBoard::checkMoveLegal(Move move) {
    if (move.isPotentialKSCastle() && isPotentialMove(move)) {
        return checkLegalCastle(move, true);
    }
    else if (move.isPotentialQSCastle() && isPotentialMove(move)) {
        return checkLegalCastle(move, false);
    }

    return isPotentialMove(move) && isPathClear(move) && simulateMove(move);
}

bool ChessBoard::isCheckMove(Move move) {
    // checks if the move made will place the OTHER player in check
    // MUST ensure that resetmove is called even if this func throws
    bool colour = move.getMovedPiece()->isWhite();
    try {
        trySetPiece(move);
        if (isInCheck(!colour)) {
            // other king in check, return true
            return true;
        }
    }
    catch (invalid_argument& err) {
        resetMove(move);
        return false;
    }
    resetMove(move);
    return false;
}

int ChessBoard::getScore(bool white) {
    int score = 0;

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            pair<int, int> curSqr = make_pair(i, j);
            if(isOccupied(curSqr)) {
                Piece *p = getPiece(curSqr);
                if (p->isWhite() == white) {
                    score += p->getPoints();
                } else {
                    score -= p->getPoints();
                }
            } 
        }
    }

    return score;
}

int ChessBoard::scoredSimulateMove(Move move) {
    if (move.getMovedPiece()->getPieceSymbol() == 'P') {
        int colDiff = move.getEndPos().second - move.getStartPos().second;
        if (colDiff != 0 && move.getCapturedPiece() == nullptr) {
            throw invalid_argument("Pawn cannot move diagonally if there is no piece to capture!");
            return false;
        }
    }

    trySetPiece(move);
    bool colour = move.getMovedPiece()->isWhite();
    int score = getScore(colour);
    // calculate the score of the top most vulnerable pieces after a simulated move
    // motivation: 2 bishops in danger more bad than 1 rook 
    // if just one piece in danger, just return score of piece
    int max1 = 0;
    int max2 = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            pair<int, int> curSqr = make_pair(i, j);
            if (isOccupied(curSqr) && getPiece(curSqr)->isWhite() == move.getMovedPiece()->isWhite()
            && checkInDanger(getPiece(curSqr))) {
                int points = getPiece(curSqr)->getPoints();
                if (points >= max1) {
                    max2 = max1;
                    max1 = points;
                } else if (points > max2) {
                    max2 = points;
                }
            }
        }
    }

    resetMove(move);

    return score - (max1 + max2);
} 

void ChessBoard::simulateFutureMove(Move move) {
    if (move.getMovedPiece()->getPieceSymbol() == 'P') {
        int colDiff = move.getEndPos().second - move.getStartPos().second;
        if (colDiff != 0 && move.getCapturedPiece() == nullptr) {
            throw invalid_argument("Pawn cannot move diagonally if there is no piece to capture!");
        }
    }

    trySetPiece(move);
}

void ChessBoard::resetFutureMove(Move move) {
    resetMove(move);
}


