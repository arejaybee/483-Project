#ifndef SUPERTICTACTOE_H
#define SUPERTICTACTOE_H

#include <string>
#include <iostream>
#include <vector>
#include "GameState.h"
using namespace std;
const int NUM_LAYERS = 3;

//WEIGHTS
const int SMALL_BOARD_WIN = 5;
const int MIDDLE_BOARD_WIN = 10;
const int CORNER_BOARD_WIN = 3;
const int CENTER_SQUARE_IN_SMALL_BOARD = 3;
const int SQUARE_IN_CENTER_BOARD = 3;
const int TWO_PARTS_OF_A_WIN = 4;
const int TWO_PARTS_OF_A_BOARD = 2;

class SuperTicTacToe
{
    public:
        //Constructor
        SuperTicTacToe();

        //plays the game
        void play();

        //prints out the board to terminal
        void printBoard();

        //gets input from player
        void getPlayerInput();

        //gets computer input
        void getCompInput();

    private:
        GameState game;
};

#endif
