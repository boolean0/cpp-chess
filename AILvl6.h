#ifndef AILvl6_H
#define AILvl6_H

#include "AI.h"

class AILvl6: public AI {
    private:
        Move generateMove() override; 

    public:
        AILvl6(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
};

#endif
