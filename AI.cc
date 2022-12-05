#include "AI.h"
#include <stdlib.h>
#include <time.h>
#include <vector>
#include <utility>
#include <stdexcept>
#include <exception> 
AI::AI(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    Player{color, inCheck, hasCastled, isComputer, board} {}

AI::~AI() {}

Move AI::handleMove() {
    return generateMove();    
}

int AI::randNumBetween(int start, int end) {
    time_t curTime = time(nullptr);
    srand(curTime);
    int num = (rand() % (end - start + 1)) + start;
    return num;
}

vector<Move> AI::getAllLegalMoves() {
    vector<Move> allMoves;
    vector<Move> legalMoves;
    ChessBoard * board = getBoard(); 
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            pair<int, int> pos = make_pair(i, j); 
            if (board->isOccupied(pos) && board->getPiece(pos)->isWhite() == getColor()) {
                Piece * p = board->getPiece(pos);
                vector<Move> moves = p->generateMoves();
                for(int i = 0; i < (int)moves.size(); i++){
                    Move m = moves[i];
                    if(board->isOccupied(m.getEndPos())){
                        moves[i] = {p, m.getStartPos(), m.getEndPos(), board->getPiece(m.getEndPos())};
                    }
                    else if (p->getPieceSymbol() == 'K' && !p->hasMoved()) {
                        moves[i] = castleMoveCreator(m);
                    }
                }
                allMoves.insert(allMoves.begin(), moves.begin(), moves.end());
            }
        }
    }

    for (int i = 0; i < (int)allMoves.size(); ++i) {
        try {
            if (board->checkMoveLegal(allMoves[i])) legalMoves.push_back(allMoves[i]);
        }
        catch (invalid_argument& err) {
            continue;
        }
    }

    return legalMoves;
}
