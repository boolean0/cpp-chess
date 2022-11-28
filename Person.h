#ifndef PERSON_H
#define PERSON_H

#include "Player.h"

class Person: public Player {
    private:
        Move parseMoveInput();
    public:
        Person(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board);
        Move handleMove() override; 
};

#endif
