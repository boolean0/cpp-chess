#ifndef PIECE_H
#define PIECE_H
#include <utility>
#include <vector>

using namespace std;
class Move;

class Piece {
    protected:
        bool white;
        int points;
        pair<int, int> position;
        char pieceSymbol;
    public:
        Piece(bool white, int points, pair<int,int> position, char pieceSymbol);
        virtual vector<Move> generateMoves();
        bool isWhite();
        int getPoints();
        char getPieceSymbol();
        pair<int, int> getPosition();
        void setPosition(pair<int, int> pos);
        virtual ~Piece();
};

#endif
