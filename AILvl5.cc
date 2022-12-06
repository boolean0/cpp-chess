#include "AILvl5.h"
#include <iostream>

using namespace std;

AILvl5::AILvl5(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl5::generateMove() {
    ChessBoard * board = getBoard();
    vector<Move> legalMoves = getAllLegalMoves(); 
    
    vector<int> scoreOfMoves;

    for (Move move: legalMoves) {
        board->simulateFutureMove(move);
        vector<Move> EnemyPotentials = getAllEnemyLegalMoves();
        
        int max = -10000000;

        for (Move moveEnemy : EnemyPotentials) {
            int score = board->scoredSimulateMove(moveEnemy); // enemy score after our move
            max = score > max ? score : max;         
        }

        scoreOfMoves.emplace_back(max); // maximum enemy score 

        board->resetFutureMove(move);
    }



    int min = 10000000;

    for (int i = 0; i < (int)scoreOfMoves.size(); ++i) {
        int score = scoreOfMoves[i];
        if (score < min) {
            min = score;
        }

    }

    vector<int> minMoves;
    for (int i = 0; i < (int)scoreOfMoves.size(); ++i) {
        if (scoreOfMoves[i] == min) {
            minMoves.emplace_back(i); 
        }
    }

    int idx = randNumBetween(0, minMoves.size() - 1);
        
    return legalMoves[minMoves[idx]];
}


