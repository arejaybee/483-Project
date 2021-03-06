/*
  SuperTicTacToe.h
  This class is used to run a game of SuperTicTacToe. It creates a gamestate, 
  then alternates between player x and player o. player input is defined by 
  the enum USER, where as the computer is broken into the enums RANDOM and TREE
 */
#ifndef SUPERTICTACTOE_H
#define SUPERTICTACTOE_H

#include <string>
#include <iostream>
#include <vector>
#include <cstdlib>
#include "GameState.h"
#include "minimax.hpp"
using namespace std;
const int NUM_LAYERS = 3;

enum moveType {
    USER,
    RANDOM,
    TREE
};

class SuperTicTacToe
{
    public:
        //Constructor
        SuperTicTacToe();

        //plays the game
        void play();

        //prints out the board to terminal
        void printBoard();

        void getInput(Piece p, moveType t);

	int getAiWin();
    private:
        //gets input from player
        void getPlayerInput(Piece p);

        //gets computer input
        void getCompInput(Piece p);

        //gets random input
        void getRandInput(Piece p);

	//gets the first available move
	void getQuickInput(Piece p);

        GameState game;

	int aiWin;
};

#endif
