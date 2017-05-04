#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

//WEIGHTS
const int SMALL_BOARD_WIN = 5;              //In score evaluation
const int MIDDLE_BOARD_WIN = 10;            //In score evaluation
const int CORNER_BOARD_WIN = 3;             //In score evaluation
const int CENTER_SQUARE_IN_SMALL_BOARD = 3; //In score evaluation
const int SQUARE_IN_CENTER_BOARD = 3;       //In score evaluation
const int TWO_PARTS_OF_A_WIN = 4;           //In score evaluation
const int TWO_PARTS_OF_A_BOARD = 2;         //In score evaluation

const int BOARD_SIZE = 9;
const int X = 1;
const int O = -1;
const string CELL_X = "\\ / x / \\";
const string CELL_O = " * * * * ";

enum Piece {
    PIECE_X = 'X',
    PIECE_O = 'O',
    PIECE_UNTAKEN = '-',
    PIECE_EMPTY = ' '
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

  GameState(GameState *g);
  
  //prints out the board to terminal
  void printBoard();
  
  char charAt(Move m);

  vector<Move> getPotentialMoves();
  
  //gets a vetor with all valid children of the current board
  vector<GameState> getPotentialChildren();

  Piece getTurn();
  
  int evaluateScore();

  //changes a piece of the board based on input
  void changeBoardPiece(Move move, Piece piece);
  
  void checkCellWon(int outerTile, Piece piece);
  
  void checkGameOver();
  
  bool gameOver;
  bool cellKnown;
  int m_cell;
  vector<string> board; //the overall board, each inner board will be a string
  Move lastMove;

 private:
};

#endif
