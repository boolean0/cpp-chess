#include "AILvl6.h"
#include <iostream>

using namespace std;

AILvl6::AILvl6(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl6::generateMove() {
    ChessBoard * board = getBoard();
    vector<Move> legalMoves = getAllLegalMoves(); 
    
    vector<int> scoreOfMoves;

    for (Move move: legalMoves) {
        board->simulateFutureMove(move);
        vector<Move> EnemyPotentials = getAllEnemyLegalMoves();
        
        //find lowest value of our followup
        //enemy prediction
        int minEnemyPrediction;

        for (Move moveEnemy : EnemyPotentials) {
            board->simulateFutureMove(moveEnemy); // enemy score after our move
            int max = 10000000;
            vector<Move> followUpMoves = getAllLegalMoves();
            for (Move followUpMove : followUpMoves) {
                int score = board->scoredSimulateMove(followUpMove);
                max = score > max ? score : max;         
            }

            board->resetFutureMove(moveEnemy);

            minEnemyPrediction = max < minEnemyPrediction ? max : minEnemyPrediction;
        }

        scoreOfMoves.emplace_back(minEnemyPrediction); // followup score expected value

        board->resetFutureMove(move);
    }


    int max = -10000000;

    for (int i = 0; i < (int)scoreOfMoves.size(); ++i) {
        int score = scoreOfMoves[i];
        if (score > max) max = score;
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
