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

using namespace std;

Game::Game(): pwScore{0}, pbScore{0}, turn{1}, isRunning{false}, isSetup{false} {
    players[0] = nullptr;
    players[1] = nullptr;
    board = new ChessBoard();   
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

    isRunning = false;
    isSetup = false;
    board = new ChessBoard();
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
                

            string s;
            while (cin >> s) {                
                if (s == "+") {
                    char piece; 
                    string pos;

                    cin >> piece >> pos; 
                    int y = pos[0] - 'a';
                    int x = pos[1] - '1';
                    cout << "x: " << x << " y: " << y << endl;
                    if (!(x >= 0 && x < 8) || !(y >= 0 && y < 8)) {
                        cerr << "invalid position" << endl;
                        continue;
                    }

                    pair<int,int> sqr = make_pair(x, y);
                    
                    switch (piece) {
                        case 'K': {
                            King * k = new King{turn, sqr};
                            board->setPiece(sqr, k);
                            break;
                        }
                        case 'Q': {
                            Queen * q = new Queen{turn, sqr};
                            board->setPiece(sqr, q);
                            break;
                        }
                            
                        case 'R': {
                            Rook * r  = new Rook{turn, sqr};
                            board->setPiece(sqr, r);
                            break;
                        }
                        case 'B': {
                            Bishop * b = new Bishop{turn, sqr};    
                            board->setPiece(sqr, b);
                            break;
                        }
                        case 'N': {
                            Knight * k = new Knight{turn, sqr};
                            board->setPiece(sqr, k);
                            break;
                        } 
                        case 'P': {
                            Pawn * p = new Pawn{turn, sqr};
                            board->setPiece(sqr, p);
                            break;
                        }
                        default: {
                            cerr << "invalid piece" << endl;
                            break;
                        }

                        
                 
                    }
                }
                else if (s == "-") {
                    string pos; 
                    cin >> pos;
                    
                    int x = pos[0] - 'a';
                    int y = pos[1] - '1';
                    
                    //handle bad input;
                    if (!(x >= 0 && x < 8) || !(y >= 0 && y < 8)) {
                        cerr << "invalid position" << endl;
                        continue;
                    }
            
                    board->setPiece(make_pair(x,y),nullptr);
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
                if (board->checkMoveLegal(curMove)) {
                    board->doMove(curMove);
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
        } 
    }

    // upon ending loop, 
    printScoreBoard();
}


