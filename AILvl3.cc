#include "AILvl3.h"
#include <iostream>
#include <exception>
#include <stdexcept>
AILvl3::AILvl3(bool color, bool inCheck, bool hasCastled, bool isComputer, ChessBoard *board):
    AI{color,inCheck,hasCastled,isComputer,board} {}

Move AILvl3::generateMove() {
    ChessBoard * board = getBoard();
    vector<Move> legalMoves = getAllLegalMoves();
    vector<pair<int, int>> inDangerPieces;
    if (legalMoves.size() == 0) throw runtime_error("No moves for AI to play!");

    // avoid capture first
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            pair<int, int> pos = make_pair(i, j); 
            if (board->isOccupied(pos) && board->getPiece(pos)->isWhite() == getColor()
            && board->checkInDanger(board->getPiece(pos))) {
                inDangerPieces.push_back(pos);
            }
        }
    }

    for (int i = 0; i < (int)legalMoves.size(); ++i) {
        for (int j = 0; j < (int)inDangerPieces.size(); ++j) {
            if (inDangerPieces[j] == legalMoves[i].getStartPos()) { 
                // this move could potentially get this piece out of danger
                if (board->isMovingOutOfDanger(legalMoves[i])) return legalMoves[i];
            }
        }
    }

    // checking/catpuring moves second
    for (Move move : legalMoves) {
        if (board->isCheckMove(move)) return move;
        
        Piece *capture = move.getCapturedPiece();
        if (capture != nullptr) {
            return move;
        }
    }


    // random third
    int idx = randNumBetween(0, legalMoves.size() - 1);
    Move m = legalMoves[idx];
    return m;

}
