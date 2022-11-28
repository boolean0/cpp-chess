#ifndef AILvl1_H
#define AILvl1_H

#include "AI.h"

class AILvl1: public AI {
    private:
        Move generateMove() override; 

    public:
        AILvl1(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
};

#endif
