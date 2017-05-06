#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <string>
#include <iostream>
#include <vector>
using namespace std;

//WEIGHTS
const int SMALL_BOARD_WIN = 10;              //In score evaluation
const int MIDDLE_BOARD_WIN = 20;            //In score evaluation
const int CORNER_BOARD_WIN = 6;             //In score evaluation
const int CENTER_SQUARE_IN_SMALL_BOARD = 3; //In score evaluation
const int SQUARE_IN_CENTER_BOARD = 3;       //In score evaluation
const int TWO_PARTS_OF_A_WIN = 8;           //In score evaluation
const int TWO_PARTS_OF_A_BOARD = 2;         //In score evaluation

const int BOARD_SIZE = 9;
const int X = 1;
const int O = -1;

//the pieces that take up boards when they are scored
const string CELL_X = "\\ / x / \\";
const string CELL_O = " * * * * ";

//all pieces that show up on board
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
  void printBoard() const;
  
  //returns the character at a Move location on the board
  char charAt(Move m) const;

  //returns all moves a player can take in a given gamestate
  vector<Move> getPotentialMoves() const;
  
  //gets a vetor with all valid children of the current board
  vector<GameState> getPotentialChildren() const;

  //returns X if it is player's turn. O if computer's turn.
  Piece getTurn() const;
  
  //determines how many points to give a computer for their min/max tree
  int evaluateScore(Piece p) const;

  //changes a piece of the board based on input
  void changeBoardPiece(Move move, Piece piece);
  
  //checks if a speciffic board has been won 
  void checkCellWon(int outerTile, Piece piece);
  
  //checks if there are three in a row on the super board
  void checkGameOver();
  
  bool gameOver; //used to see if game has been won
  bool cellKnown; //if the cell a player must go to is known
  int m_cell; //the cell a player must go ot
  vector<string> board; //the overall board, each inner board will be a string
  Move lastMove; //the move that was placed to get to this Gamestate

 private:
};

#endif
