#include "AI.h"
AI::AI(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    Player{color, inCheck, hasCastled, isComputer, board} {}

AI::~AI() {}

Move AI::handleMove() {
    return generateMove();    
}
