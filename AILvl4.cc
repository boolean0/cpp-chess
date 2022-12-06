#include "AILvl4.h"

AILvl4::AILvl4(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl4::generateMove() {
    ChessBoard * board = getBoard();
    vector<Move> legalMoves = getAllLegalMoves(); 
    
    vector<int> scoreOfMoves;

    for (Move move: legalMoves) {
        scoreOfMoves.emplace_back(board->scoredSimulateMove(move));
    }

    int idxMax = 0;
    int max = -10000000;

    for (int i = 0; i < (int)scoreOfMoves.size(); ++i) {
        int score = scoreOfMoves[i];
        if (score > max) {
            max = score;
            idxMax = i;
        }
    }
    
    return legalMoves[idxMax];
}
