#include "AILvl4.h"
#include <iostream>

using namespace std;

AILvl4::AILvl4(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl4::generateMove() {
    ChessBoard * board = getBoard();
    vector<Move> legalMoves = getAllLegalMoves(); 
    
    vector<int> scoreOfMoves;

    for (Move move: legalMoves) {
        scoreOfMoves.emplace_back(board->scoredSimulateMove(move));
    }

    int max = -10000000;

    for (int i = 0; i < (int)scoreOfMoves.size(); ++i) {
        int score = scoreOfMoves[i];
        if (score > max) {
            max = score;
        }
    }

    vector<int> maxMoves;
    for (int i = 0; i < (int)scoreOfMoves.size(); ++i) {
        if (scoreOfMoves[i] == max) {
            maxMoves.emplace_back(i); 
        }
    }

    int idx = randNumBetween(0, maxMoves.size() - 1);
        
    return legalMoves[maxMoves[idx]];
}
