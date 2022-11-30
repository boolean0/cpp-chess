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
    delete board;
    delete players[0];
    delete players[1];
    delete textView;
    delete graphicsView;

    isRunning = false;
    isSetup = false;
    board = new ChessBoard();
    textView = new TextObserver{board}; 
    graphicsView = new GraphicsObserver{board};
    players[0] = nullptr;
    players[1] = nullptr; // white is 1, black is 0
}

void assignPlayers(string player, int idx, Player** players, ChessBoard * board) {
            if (player == "human") {
                players[idx] = new Person{1, false, false, false, board};
            } 
            else if (player == "computer1") {
                players[idx] = new AILvl1{1, false, false, true, board};
            }   
            else if (player == "computer2") {
                players[idx] = new AILvl2{1, false, false, true, board};
            }
            else if (player == "computer3") {
                players[idx] = new AILvl3{1, false, false, true, board};
            }
            else if (player == "computer4") {
                players[idx] = new AILvl4{1, false, false, true, board};
            }
            else {
                string colour = idx == 1 ? "White" : "Black";
                cerr << "Invalid" << colour << "player." << endl;
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
            cerr << "invalid piece" << endl;
            break;
        }
    }
}

void Game::startGame() {
    bool isRunning = false;
    bool isSetup = false; 

    string input;
    cout << "Starting Chess Environment" << endl;
    while(cin >> input) {
        Player *cur = players[turn];
        // make sure we prevent people from trying to move before starting a game
        if (input == "print") {
            //delete later, for testing
            board->printCLI();
        }
        
        if (input == "game") {
            string pW, pB;
            cin >> pW >> pB;
            assignPlayers(pW, 1, players, board);
            assignPlayers(pB, 0, players, board);
            isRunning = true;
        } else if (input == "setup") {
            if (isRunning) {
                cerr << "Game is already running; cannot enter setup mode!" << endl;
                continue;       
            }

            if (!isSetup) {
                board->init();
                isSetup = true;
            }
                
            // TODO: put into rows and cols instead of x,y
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

                    //TODO ? : add try catch
                    addPiece(piece, sqr);
                }
                else if (s == "-") {
                    char piece;
                    string pos; 
                    cin >> piece >> pos;
                    
                    int col = pos[0] - 'a';
                    int row = pos[1] - '1';
                    
                    //handle bad input;
                    if (!(col >= 0 && col < 8) || !(row >= 0 && row < 8)) {
                        cerr << "invalid position" << endl;
                        continue;
                    }
            
                    board->setPiece(make_pair(row, col),nullptr);
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
                    break;
                }
            }


        } else if (input == "move") {
            try{
                Move curMove = cur->handleMove();
                board->printCLI();
               if (board->checkMoveLegal(curMove)) {
                    board->doMove(curMove);
                    board->printCLI();
               }
            }
            catch (std::invalid_argument& err) {
                cerr << err.what() << endl;
                continue;
            }
            //TODO: check validity

            //TODO: update player states  

            turn = !turn;

        } else if (input == "resign") {
            if (cur->getColor() == 1) { //white resigns
                pbScore++;
            } else { //black resigns
                pwScore++;
            }
            reset();
        } else if(input == "test"){

            addPiece('P', make_pair(3, 0));
        }
    }

    // upon ending loop, 
    //printScoreBoard();
}


