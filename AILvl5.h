#ifndef AILvl5_H
#define AILvl5_H

#include "AI.h"

class AILvl5: public AI {
    private:
        Move generateMove() override; 

    public:
        AILvl5(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
};

#endif
