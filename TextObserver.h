#ifndef TEXTOBSERVER_H
#define TEXTOBSERVER_H
#include "Observer.h"
#include "ChessBoard.h"

class TextObserver : public Observer {
    private:
        ChessBoard *board;
    public:
        TextObserver(ChessBoard *board);
        void notify() override;
        ~TextObserver();
};


#endif
