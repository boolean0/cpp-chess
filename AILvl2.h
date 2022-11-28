#ifndef AILvl2_H
#define AILvl2_H

#include "AI.h"

class AILvl2: public AI {
    private:
        Move generateMove() override; 

    public:
        AILvl2(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
};

#endif
