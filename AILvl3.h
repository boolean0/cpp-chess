#ifndef AILvl3_H
#define AILvl3_H

#include "AI.h"

class AILvl3: public AI {
    private:
        Move generateMove() override; 

    public:
        AILvl3(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
};

#endif
