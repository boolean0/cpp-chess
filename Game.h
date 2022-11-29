#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "ChessBoard.h"

class Game {
    private:
        Player * players[2];
        int pwScore;
        int pbScore;
        bool turn;
        ChessBoard *board;
        bool isRunning;
        bool isSetup;
        void printScoreBoard(); 
        void reset();
    public:
        Game();
        ~Game(); 
        void startGame();
};

#endif
