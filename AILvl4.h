#ifndef AILvl4_H
#define AILvl4_H

#include "AI.h"

class AILvl4: public AI {
    private:
        Move generateMove() override; 

    public:
        AILvl4(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
};

#endif
