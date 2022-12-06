#ifndef AI_H
#define AI_H

#include "Player.h"

class AI: public Player {
    private:
        virtual Move generateMove() = 0; 

    public:
        AI(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
        ~AI(); 
        int randNumBetween(int start, int end);
        Move handleMove() override; 
        vector<Move> getAllLegalMoves();
        vector<Move> getAllEnemyLegalMoves();
};

#endif
