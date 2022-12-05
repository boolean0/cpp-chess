#include "AILvl2.h"
#include "Piece.h"
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;

AILvl2::AILvl2(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl2::generateMove() {
    //TODO!!!!!!!!!!!!! 
    vector<Move> legalMoves = getAllLegalMoves(); // no moves case? 
    if (legalMoves.size() == 0) throw runtime_error("No moves for AI to play!");
    for (auto move : legalMoves) {
        Piece *capture = move.getCapturedPiece();
        if (capture != nullptr) {
            return move;
        }
    }

    int idx = randNumBetween(0, legalMoves.size() - 1);
    Move m = legalMoves[idx];
    
    return m;
}
