#include "Piece.h"
#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "Bishop.h"
#include <utility> 
#include <vector> 
#include <iostream> 

int main() {
    ChessBoard board{};
    board.init(); 
    // testing harness
    while (1) {
        int x, y; 
        int color; // 1 = white, 0 = black
        char c; 
        string command; 
        cin >> command; 
        if (command == "set") {
            cin >> x >> y >> c >> color; 
            pair<int,int> sqr = make_pair(x, y);
            switch (c) {
                case 'K': {
                    King * k = new King{color, sqr};
                    board.setPiece(sqr, k);    
                    break;
                }
                case 'Q': {
                    Queen * q = new Queen{color, sqr};
                    board.setPiece(sqr, q);
                    break;
                }
                    
                case 'R': {
                    Rook * r  = new Rook{color, sqr};
                    board.setPiece(sqr, r);
                    break;
                }
                case 'B': {
                    Bishop * b = new Bishop{color, sqr};    
                    board.setPiece(sqr, b);
                    break;
                }
                case 'N': {
                    Knight * k = new Knight{color, sqr};
                    board.setPiece(sqr, k);
                    break;
                } 
                case 'P': {
                    Pawn * p = new Pawn{color, sqr};
                    board.setPiece(sqr, p);
                    break;
                }
            }
        }
        else if(command == "get"){
            cin >> x >> y;
            if(board.isOccupied(make_pair(x,y))) cout << board.getPiece(make_pair(x,y))->getPieceSymbol();
            Piece *p = board.getPiece(make_pair(x,y));
            vector<Move> ml = p->generateMoves();
            for(Move i : ml){
                int x = i.getEndPos().first;
                int y = i.getEndPos().second;
                cout << x << "," << y << endl;
            }
        }
        else if (command == "print") {
            board.printCLI();
        }
    }



    
}
