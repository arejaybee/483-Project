#ifndef SUPERTICTACTOE_H
#define SUPERTICTACTOE_H

#include <string>
#include <iostream>
#include <vector>
#include "GameState.h"
using namespace std;
const int NUM_LAYERS = 3;

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
