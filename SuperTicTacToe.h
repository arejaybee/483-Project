#ifndef SUPERTICTACTOE_H
#define SUPERTICTACTOE_H

#include <string>
#include <iostream>
using namespace std;
const int BOARD_SIZE = 9;
const string CELL_X = "\\ / x / \\";
const string CELL_O = " * * * * ";
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
  void changeBoardPiece(int outerTile, int innerTile, string piece);

  void checkCellWon(int outerTile, string piece);
  void checkGameOver();
 private:
  string board[BOARD_SIZE]; //the overall board, each inner board will be a string
  bool cellKnown;
  int m_cell;
  bool gameWon;
};

#endif
