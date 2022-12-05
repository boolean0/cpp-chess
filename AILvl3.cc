#include "AILvl3.h"
#include <iostream>
#include <exception>
#include <stdexcept>
AILvl3::AILvl3(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl3::generateMove() {
    //TODO!!!!!!!!!!!!! 
    vector<Move> legalMoves = getAllLegalMoves();
    if (legalMoves.size() == 0) throw runtime_error("No moves for AI to play!");
    return Move{};
}
