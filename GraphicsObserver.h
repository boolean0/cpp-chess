#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "Observer.h"
#include "ChessBoard.h"

class GraphicsObserver : public Observer {
    private:
        ChessBoard *board;
    public:
        GraphicsObserver(ChessBoard *board);
        void notify() override;
        ~GraphicsObserver();
};


#endif
