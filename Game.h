#ifndef GAME_H
#define GAME_H

#include "Player.h"
#include "ChessBoard.h"
#include "Observer.h"

class Game {
    private:
        Player * players[2];
        Player * helpers[2];
        int pwScore;
        int pbScore;
        bool turn;
        ChessBoard *board;
        Observer *textView;
        Observer *graphicsView;
        bool isRunning;
        bool isSetup;
        void printScoreBoard(); 
        void reset();
        void addPiece(char piece, pair<int,int> sqr);
        bool existsTwoKings();
    public:
        Game();
        ~Game(); 
        void startGame();
};

#endif
