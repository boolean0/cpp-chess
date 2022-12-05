#include "AILvl1.h"
#include <stdlib.h>
#include <iostream>
#include <exception>
#include <stdexcept>
using namespace std;
AILvl1::AILvl1(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl1::generateMove() {
    vector<Move> legalMoves = getAllLegalMoves(); // no moves case? 
    if (legalMoves.size() == 0) throw runtime_error("No moves for AI to play!");
    int idx = randNumBetween(0, legalMoves.size() - 1);
    Move m = legalMoves[idx];
    return m;
}   
