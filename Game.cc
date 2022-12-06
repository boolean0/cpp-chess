#include <iostream>
#include <string>
#include <utility>
#include "Game.h"
#include "Move.h"
#include "Piece.h"
#include "Person.h"
#include "AI.h"
#include "AILvl1.h"
#include "AILvl2.h"
#include "AILvl3.h"
#include "AILvl4.h"
#include "AILvl5.h"
#include "AILvl6.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Knight.h"
#include "Pawn.h"
#include "Bishop.h"
#include "TextObserver.h"
#include "GraphicsObserver.h"

using namespace std;

Game::Game(): pwScore{0}, pbScore{0}, turn{1}, isRunning{false}, isSetup{false} {
    players[0] = nullptr;
    players[1] = nullptr;
    helpers[0] = nullptr;
    helpers[1] = nullptr;
    board = new ChessBoard();   
    textView = new TextObserver{board}; 
    graphicsView = new GraphicsObserver{board};
}

Game::~Game() {
    delete board;
    delete players[0];
    delete players[1];
}

void Game::printScoreBoard() {
    cout << "Final Score:" << endl;
    cout << "White: " << pwScore << endl;
    cout << "Black: " << pbScore << endl;
}

void Game::reset() {
   // delete board;
    delete players[0];
    delete players[1];
    delete helpers[0];
    delete helpers[1];
    delete textView;
    delete graphicsView;

    isRunning = false;
    isSetup = false;
    board = new ChessBoard();
    textView = new TextObserver{board};
    graphicsView = new GraphicsObserver{board};
    players[0] = nullptr;
    players[1] = nullptr; // white is 1, black is 0
    turn = 1;
}

void assignPlayers(string player, int idx, Player** players, Player** helpers, ChessBoard * board) {
            if (player == "human") {
                players[idx] = new Person{(bool)idx, false, false, false, board};
                helpers[idx] = new AILvl5{(bool)idx, false, false, true, board};
            } 
            else if (player == "computer1") {
                players[idx] = new AILvl1{(bool)idx, false, false, true, board};
            }   
            else if (player == "computer2") {
                players[idx] = new AILvl2{(bool)idx, false, false, true, board};
            }
            else if (player == "computer3") {
                players[idx] = new AILvl3{(bool)idx, false, false, true, board};
            }
            else if (player == "computer4") {
                players[idx] = new AILvl4{(bool)idx, false, false, true, board};
            }
            else if (player == "computer5") {
                players[idx] = new AILvl5{(bool)idx, false, false, true, board};
            }
            /*else if (player == "computer6") {
                players[idx] = new AILvl6{(bool)idx, false, false, true, board};
            }*/
            else {
                string colour = idx == 1 ? "White" : "Black";
                string err = "Invalid " + colour + " player.";
                throw invalid_argument(err);
            }
}

void Game::addPiece(char piece, pair<int,int> sqr) {
     switch (piece) {
        case 'K': {
            King * k = new King{1, sqr};
            board->setPiece(sqr, k);
            break;
        }
        case 'Q': {
            Queen * q = new Queen{1, sqr};
            board->setPiece(sqr, q);
            break;
        }
            
        case 'R': {
            Rook * r  = new Rook{1, sqr};
            board->setPiece(sqr, r);
            break;
        }
        case 'B': {
            Bishop * b = new Bishop{1, sqr};    
            board->setPiece(sqr, b);
            break;
        }
        case 'N': {
            Knight * k = new Knight{1, sqr};
            board->setPiece(sqr, k);
            break;
        } 
        case 'P': {
            Pawn * p = new Pawn{1, sqr};
            board->setPiece(sqr, p);
            break;
        }
        case 'k': {
            King * k = new King{0, sqr};
            board->setPiece(sqr, k);
            break;
        }
        case 'q': {
            Queen * q = new Queen{0, sqr};
            board->setPiece(sqr, q);
            break;
        }
            
        case 'r': {
            Rook * r  = new Rook{0, sqr};
            board->setPiece(sqr, r);
            break;
        }
        case 'b': {
            Bishop * b = new Bishop{0, sqr};    
            board->setPiece(sqr, b);
            break;
        }
        case 'n': {
            Knight * k = new Knight{0, sqr};
            board->setPiece(sqr, k);
            break;
        } 
        case 'p': {
            Pawn * p = new Pawn{0, sqr};
            board->setPiece(sqr, p);
            break;
        }
        default: {
            throw invalid_argument("Invalid piece");
        }
    }
}

bool Game::existsTwoKings(){
    int whiteKing = 0;
    int blackKing = 0;
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece *p = board->getPiece({i,j});
            if(p != nullptr) {
                if (p->getPieceSymbol() == 'K' && p->isWhite()) 
                    whiteKing++;
                else if (p->getPieceSymbol() == 'K' && !p->isWhite())
                    blackKing++;
            }
        }
    }
    if(whiteKing == 1 && blackKing == 1) 
        return true;
    else
        return false;
}

void Game::printWinner(bool colour) {
    string winner = colour ? "White" : "Black"; 
    cout << winner << " won! Use setup and game to start a new game." << endl;
}

void Game::printDraw(){
    cout << "Draw! Use setup and game to start a new game." << endl;
}

void Game::startGame() {
    isRunning = false;
    isSetup = false; 
    Player *cur = nullptr;
    string input;
    cout << "Starting Chess Environment" << endl;
    while(cin >> input) {
        if (input == "print") {
            board->notifyObservers();
        }
        
        else if (input == "game") {
            string pW, pB;
            cin >> pW >> pB;
            try {
                assignPlayers(pW, 1, players, helpers, board);
                assignPlayers(pB, 0, players, helpers, board);
                isRunning = true;
            } catch (std::invalid_argument& err) {
                delete players[0];
                delete players[1];
                cerr << err.what() << endl;
            }
            
        } 
        
        else if (input == "setup") {
            if (isRunning) {
                cerr << "Game is already running; cannot enter setup mode!" << endl;
                continue;       
            }

            if (!isSetup) {
                board->init();
                isSetup = true;
            }

            string s;
            while (cin >> s) {                
                if (s == "+") {
                    char piece; 
                    string pos;

                    cin >> piece >> pos; 
                    int col = pos[0] - 'a';
                    int row = pos[1] - '1';
                    if (!(row >= 0 && row < 8) || !(col >= 0 && col < 8)) {
                        cerr << "invalid position" << endl;
                        continue;
                    }
                    pair<int,int> sqr = make_pair(row, col);

                    try{
                        addPiece(piece, sqr);
                    } catch(char const* invalidPieceMsg) {
                        cerr << invalidPieceMsg << endl;
                        continue;
                    }

                    board->notifyObservers();
                }
                else if (s == "-") {
                    string pos; 
                    cin >> pos;
                    int col = pos[0] - 'a';
                    int row = pos[1] - '1';
                    
                    //handle bad input;
                    if (!(col >= 0 && col < 8) || !(row >= 0 && row < 8)) {
                        cerr << "invalid position" << endl;
                        continue;
                    }
           
                    board->setPiece(make_pair(row, col),nullptr);
                    board->notifyObservers();
                } 
                else if (s == "=") {
                    string color;
                    cin >> color;

                    if (color == "white") {
                        turn = 1;
                    } 
                    else if (color == "black") {
                        turn = 0;
                    } else {
                        cerr << "bad color!" << endl;
                    }
                }
                else if (s == "done") {
                    bool validSetup = true;
                    if (!existsTwoKings()) {
                        cerr << "Invalid setup: must have two kings" << endl;
                        validSetup = false;
                    } else if (board->isInCheck(true) || board->isInCheck(false)) {
                        cerr << "Invalid setup: cannot start in check" << endl;
                        validSetup = false;
                    } else if (board->isInsufficientMaterial()) {
                        cerr << "Invalid setup: insufficient material" << endl;
                        validSetup = false;
                    }
                    if(validSetup){
                        break;
                    }
                }
                else if(s == "default") {
                    addPiece('R', make_pair(0, 0));
                    addPiece('N', make_pair(0, 1));
                    addPiece('B', make_pair(0, 2));
                    addPiece('Q', make_pair(0, 3));
                    addPiece('K', make_pair(0, 4));
                    addPiece('B', make_pair(0, 5));
                    addPiece('N', make_pair(0, 6));
                    addPiece('R', make_pair(0, 7));
                    for(int i = 0; i < 8; i++){
                        addPiece('P', make_pair(1, i));
                    }
                    addPiece('r', make_pair(7, 0));
                    addPiece('n', make_pair(7, 1));
                    addPiece('b', make_pair(7, 2));
                    addPiece('q', make_pair(7, 3));
                    addPiece('k', make_pair(7, 4));
                    addPiece('b', make_pair(7, 5));
                    addPiece('n', make_pair(7, 6));
                    addPiece('r', make_pair(7, 7));
                    for(int i = 0; i < 8; i++){
                        addPiece('p', make_pair(6, i));
                    }
                    board->notifyObservers();
                }
            }


        } else if (input == "move") {
            if (!isRunning) {
                cerr << "No game is running yet!" << endl;
                continue;
            }
            try{
                Move curMove = cur->handleMove(); // can throw invalid arg
                if (board->checkMoveLegal(curMove)) {
                    board->doMove(curMove);
                    board->notifyObservers();
                    //checking checkmate & stalemate
                    Player * opp = players[!turn];
                    if(board->isInCheck(opp->getColor())){
                        opp->setInCheck(true);
                        if (turn == 0) cout << "White "; // black put white in check
                        else cout << "Black ";
                        cout << "is in check." << endl;
                    }
                    if(opp->isCheckmate()){
                        cout << "Checkmate! ";
                        if(opp->getColor() == 1) {
                            
                            pbScore++;
                        } 
                        else{
                            pwScore++;
                        }
                        printWinner(cur->getColor());
                        reset();
                    } else if(opp->isStalemate()){
                        cout << "Stalemate! ";
                        printDraw();
                        pbScore += 0.5;
                        pwScore += 0.5;
                        reset();
                    } else if(board->isInsufficientMaterial()){
                        cout << "Insufficient Material! " << endl;
                        printDraw();
                        pbScore += 0.5;
                        pwScore += 0.5;
                        reset();
                    }
                    turn = !turn; // only when a valid move is played do we switch turns
               }
            }
            catch (std::invalid_argument& err) {
                cerr << err.what() << endl;
                //continue;
            }
            //TODO: check validity

            //TODO: update player states 

        } else if (input == "hint") {
            if (helpers[turn] == nullptr) {
                cout << "Hint can only be called by a human!" << endl;
                continue;
            }

            cout << "Select level of guidance [0-1]:" << endl;
            int i = -1;
            while (i != 0 && i != 1) {
                cin >> i;
            }
            cout << "Thinking really hard..." << endl;

            try {
                Move hint = helpers[turn]->handleMove();
                cout << "Move " << hint.getMovedPiece()->getPieceSymbol() << " on " 
                     << char(hint.getStartPos().second + 'A') << hint.getStartPos().first + 1;

                if (i == 1) {
                    cout << " to " << char(hint.getEndPos().second + 'A') << hint.getEndPos().first + 1;;
                } 

                cout << endl;

            } catch (std::invalid_argument& err) {
                cerr << err.what() << endl;
            }

        } else if (input == "undo") {
            try {
                board->undo();
                turn = !turn;
                board->notifyObservers(); 
            }
            catch (out_of_range& err) {
                cout << err.what() << endl;
            }

        } else if (input == "resign") {
            if (cur->getColor() == 1) { //white resigns
                pbScore++;
            } else { //black resigns
                pwScore++;
            }
            printWinner(!cur->getColor());
            reset();
            continue;
        }


        
        if (isRunning) { // both players initialized, game is running, prompt move from the other player
             string colorsTurn = turn ? "White " : "Black ";
            cout << colorsTurn << "to play:" << endl;
            cur = players[turn];
        }
    }

    // upon ending loop, 
    printScoreBoard();
}
