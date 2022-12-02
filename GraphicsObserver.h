#ifndef VIEW
#define VIEW 0 
#endif

#ifndef GRAPHICSOBSERVER_H
#define GRAPHICSOBSERVER_H
#include "Observer.h"
#include "ChessBoard.h"

#if VIEW >= 1 
    #include "Window.h"
#endif

class GraphicsObserver : public Observer {
    private:
        ChessBoard *board;
        #if VIEW >= 1 
        Xwindow *window;
        #endif
    public:
        GraphicsObserver(ChessBoard *board);
        void notify() override;
        ~GraphicsObserver();
};


#endif
