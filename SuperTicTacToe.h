#ifndef SUPERTICTACTOE_H
#define SUPERTICTACTOE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;
const int BOARD_SIZE = 9;
const string CELL_X = "\\ / x / \\";
const string CELL_O = " * * * * ";
enum Piece {PIECE_X = 'X', PIECE_O = 'O'};

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


        //changes a piece of the board based on input
        void changeBoardPiece(int outerTile, int innerTile, Piece piece);

        void checkCellWon(int outerTile, Piece piece);
        void checkGameOver();
    private:
        vector<string> board; //the overall board, each inner board will be a string
        bool cellKnown;
        int m_cell;
        bool gameWon;
};

#endif
