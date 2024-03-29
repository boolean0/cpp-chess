#ifndef VIEW
#define VIEW 0
#endif 

#include <iostream>
#include "GraphicsObserver.h"
#include "Window.h"

using namespace std;

GraphicsObserver::GraphicsObserver(ChessBoard *board): board{board} {
    board->attach(this);

    #if VIEW >= 1 
        window = new Xwindow(900,900);
    #endif
}

GraphicsObserver::~GraphicsObserver() {
    board->detach(this);
    #if VIEW >= 1
        delete window;
    #endif

}

void GraphicsObserver::notify() {
    #if VIEW >= 1
    /*
    for(int i = 7; i >= 0; --i){ //starts from a8 (0,0)
        for(int j = 0; j < 8; j++){
            int xCor = 100*j;
            int yCor = 100*(7-i);
            
            bool isWhiteSquare = ((i+j)%2 == 0);

            if (isWhiteSquare) window->fillRectangle(xCor,yCor,100,100,window->White);
            else window->fillRectangle(xCor,yCor,100,100,window->Black);
            
        }
    }

    */
   
    //window->f();
    for(int j = 0; j < 8; j++){
        for(int i = 7; i >= 0; --i){ //starts from a8 (0,0)
            int xCor = 50+100*(j);
            int yCor = 50+100*(7-i);
            
            bool isWhiteSquare = ((i+j)%2 == 1);

            if(board->isOccupied(make_pair(i, j))) {
                Piece* piece = board->getPiece(make_pair(i, j));   
                bool isWhitePiece = piece->isWhite();
                char p = piece->getPieceSymbol();
                window->drawPiece(p, isWhitePiece, isWhiteSquare, xCor, yCor);
            } else {
                if (isWhiteSquare) window->fillRectangleCustom(xCor,yCor,100,100,3);
                else window->fillRectangleCustom(xCor,yCor,100,100,2);
            }
        }
    }
    
    
    #endif 
}
