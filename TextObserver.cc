#include <iostream>
#include "TextObserver.h"

using namespace std;

TextObserver::TextObserver(ChessBoard *board): board{board} {
    board->attach(this);
}

TextObserver::~TextObserver() {
    board->detach(this);
}

void TextObserver::notify() {
    for(int i = 7; i >= 0; --i){ //starts from a8 (0,0)
        cout << i + 1 << "  ";
        for(int j = 0; j < 8; j++){
            if(board->isOccupied(make_pair(i, j))){
                Piece* piece = board->getPiece(make_pair(i, j));
                if(piece->isWhite()){
                    cout << piece->getPieceSymbol();
                } else {
                    char lower = tolower(piece->getPieceSymbol());
                    cout << lower;
                }
            } else {
                //check for white or black square
                if((i+j)%2 == 0){
                    cout << ' ';
                } else{
                    cout << '_';
                }
            }
        }
        cout << endl;
    }
    
    cout << endl << "   ABCDEFGH" << endl;

}
