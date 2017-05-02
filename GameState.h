#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

const int BOARD_SIZE = 9;
const int X = 1;
const int O = -1;
const string CELL_X = "\\ / x / \\";
const string CELL_O = " * * * * ";

enum Piece {
    PIECE_X = 'X',
    PIECE_O = 'O'
};

struct Move {
    int board;
    int square;
};

class GameState
{
 public:
  //Constructor
  GameState();
  
  //prints out the board to terminal
  void printBoard();
  
  char charAt(Move m);
  
  //gets a vetor with all valid children of the current board
  vector<GameState> getPotentialChildren();
  
  //updates the board state using the input move
  int makeMove(Move m);
  
  //changes a piece of the board based on input
  void changeBoardPiece(Move move, Piece piece);
  
  void checkCellWon(int outerTile, Piece piece);
  
  void checkGameOver();
  
  bool gameOver;
  
  bool cellKnown;
  int m_cell;
 private:
  vector<string> board; //the overall board, each inner board will be a string
  Move lastMove;
};

#endif
