#include "GameState.h"

using namespace std;

//generic constructor
GameState::GameState() : gameOver(false) , gameTie(false) , cellKnown(false) , m_cell(-1) , board(BOARD_SIZE) , lastMove(Move()) 
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board.at(i) = "---------";
    }
}

//copy constructor
GameState::GameState(GameState *g) : gameOver(false) , gameTie(false), cellKnown(false) , m_cell(-1) , board(BOARD_SIZE) , lastMove(Move()) 
{
  gameOver = g->gameOver;
  gameTie = g->gameTie;
  cellKnown = g->cellKnown;
  m_cell = g->m_cell;
  board = g->board;
  lastMove = g->lastMove;
}

//This is witchcraft
void GameState::printBoard() const
{
  //top of board
    cout << " _____________________________\n\n";

    for (int i = 0; i < BOARD_SIZE; i += 3)
    {
      //three square rows per board row 
      for (int j = 0; j < 3; j++)
        {
	  cout << " || ";
	  //print a square row of values
	  for (int k = 0; k < 3; k++)
            {
	      cout << board.at(k + i).at(0 + (j * 3)) << " " <<
		board.at(k + i).at(1 + (j * 3)) << " " <<
		board.at(k + i).at(2 + (j * 3)) << " ";
	      cout << "|| ";
            }
	  
	  cout << endl;
        }
      //bottom of each row
      if (i % 3 == 0) {
	cout << " _____________________________\n\n";
      }
    }
    
    cout << endl << endl;
}


//just see if there is a char at the move option provided
char GameState::charAt(Move m) const
{
    return board.at(m.board).at(m.square);
}

//a vector of places a player CAN move to
vector<Move> GameState::getPotentialMoves() const
{
  vector<Move> potentialMoves;
  Move tempMove;

  //if the computer has an assigned board
  if (cellKnown) {
    //look for hiphens in that board, and return those
    tempMove.board = lastMove.square;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (board[lastMove.square][i] == PIECE_UNTAKEN) {
        tempMove.square = i;
        potentialMoves.push_back(tempMove);
      }
    }
  }
  //otherwise look for hiphens anywhere
  else {
    for (int i = 0; i < BOARD_SIZE; i++) {
      for (int j = 0; j < BOARD_SIZE; j++) {
        if (board[i][j] == PIECE_UNTAKEN) {
          tempMove.board = i;
          tempMove.square = j;
          potentialMoves.push_back(tempMove);
        }
      }
    }
  }

  return potentialMoves;
}

//return all possible gamestates to come from this one
vector<GameState> GameState::getPotentialChildren() const
{
  vector<GameState> children;

  //find out where the player could move to
  vector<Move> possibleMoves = getPotentialMoves();
  int numPossibleMoves = possibleMoves.size();
  
  //for each move, generate a gamestate where that move was taken
  for (int i = 0; i < numPossibleMoves; i++) {
    //cout << possibleMoves[i].board << ", " << possibleMoves[i].square << endl;
    GameState tempGameState = GameState(*this);
    tempGameState.changeBoardPiece(possibleMoves[i], getTurn());
    children.push_back(tempGameState);
  }

  return children;
}

//lets you know who's turn it is
Piece GameState::getTurn() const
{
  if (board[lastMove.board][lastMove.square] == PIECE_X) {
    return PIECE_O;
  }
  else if (board[lastMove.board][lastMove.square] == PIECE_O) {
    return PIECE_X;
  }
  //for debugging, this should never happpen
  else {
    return PIECE_EMPTY;
  }
}

//determine the score of this boardstate (for computer's min/max tree)
int GameState::evaluateScore(Piece p) const
{
  string c;
  string oc;
  Piece op;
  if (p == PIECE_X) {
    c = CELL_X;
    oc = CELL_O;
    op = PIECE_O;
  }
  else if (p == PIECE_O) {
    c = CELL_O;
    oc = CELL_X;
    op = PIECE_X;
  }
  int score = 0;
  Piece turn  = getTurn();

  if(turn == p && gameOver)
    {
      score += 1000;
    }
  else if(turn == op && gameOver)
    {
      score -= 1000;
    }
  for(int i = 0; i < BOARD_SIZE; i++) {
    //for winning any board, you get SMALL_BOARD_WIN points
    if(board[i] == c) {
      score += SMALL_BOARD_WIN;
    }
    else if(board[i] == oc){
      score -= SMALL_BOARD_WIN;
    }

    //if 2/3 squares are PIECE_O, you get TWO_PARTS_OF_A_BOARD points
    if(board[i][0] == p) {
      for(int j = 1; j < 9; j++) {
        if(board[i][j] == p && j != 5 && j!= 7) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][1] == p) {
      for(int j = 2; j < 9; j++) {
        if(board[i][j] == p && j != 3 && j!= 5 && j!=6 && j!=8) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][2] == p) {
      for(int j = 3; j < 9; j++) {
        if(board[i][j] == p && j!= 7) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][3] == p) {
      for(int j = 4; j < 9; j++) {
        if(board[i][j] == p && j!= 7 && j!=8) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][4] == p) {
      for(int j = 5; j < 9; j++) {
        if(board[i][j] == p) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][5] == p) {
      for(int j = 6; j < 9; j++) {
        if(board[i][j] == p && j!= 7) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][6] == p) {
      for(int j = 7; j < 9; j++) {
        if(board[i][j] == p) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][7] == p) {
      for(int j = 8; j < 9; j++) {
        if(board[i][j] == p) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }

    //this section loses points if the player has those spots
    if(board[i][0] == op) {
      for(int j = 1; j < 9; j++) {
        if(board[i][j] == op && j != 5 && j!= 7) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][1] == op) {
      for(int j = 2; j < 9; j++) {
        if(board[i][j] == op && j != 3 && j!= 5 && j!=6 && j!=8) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][2] == op) {
      for(int j = 3; j < 9; j++) {
        if(board[i][j] == op && j!= 7) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][3] == op) {
      for(int j = 4; j < 9; j++) {
        if(board[i][j] == op && j!= 7 && j!=8) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][4] == op) {
      for(int j = 5; j < 9; j++) {
        if(board[i][j] == op) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][5] == op) {
      for(int j = 6; j < 9; j++) {
        if(board[i][j] == op && j!= 7) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][6] == op) {
      for(int j = 7; j < 9; j++) {
        if(board[i][j] == op) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][7] == op) {
      for(int j = 8; j < 9; j++) {
        if(board[i][j] == op) {
          score -= TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    
    //if the center is an O you get an additional CENTER_SQUARE_IN_SMALL_BOARD points
    if(board[i][4] == p) {
      score += CENTER_SQUARE_IN_SMALL_BOARD;
    }
    else if(board[i][4] == op) {
      score -= CENTER_SQUARE_IN_SMALL_BOARD;
    }
  }

  //gain SQUARE_IN_CENTER_BOARD points for every square you own in the center board
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[4][i] == p) {
      score += SQUARE_IN_CENTER_BOARD;
    }
    else if (board[4][i] == op) {
      score -= SQUARE_IN_CENTER_BOARD;
    }
  }

  //winning the center board is an additional MIDDLE_BOARD_WIN points
  if(board[4] == c) {
    score += MIDDLE_BOARD_WIN;
  }
  if(board[4] == oc) {
    score -= MIDDLE_BOARD_WIN;
  }
  
  //winning a corner is an additional CORNER_BOARD_WIN points
  if(board[0] == c || board[2] == c || board[6] == c || board[8] == c) {
    score += CORNER_BOARD_WIN;
  }
  else if(board[0] == oc || board[2] == oc || board[6] == oc || board[8] == oc) {
    score -= CORNER_BOARD_WIN;
  }
  
  //if you have 2/3 parts needed to win, thats TWO_PARTS_OF_A_WIN points
  if(board[0] == c) {
    for(int j = 1; j < 9; j++) {
      if(board[j] == c && j != 5 && j!= 7) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[1] == c) {
    for(int j = 2; j < 9; j++) {
      if(board[j] == c && j != 3 && j!= 5 && j!=6 && j!=8) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[2] == c) {
    for(int j = 3; j < 9; j++) {
      if(board[j] == c && j!= 7) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[3] == c) {
    for(int j = 4; j < 9; j++) {
      if(board[j] == c && j!= 7 && j!=8) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[4] == c) {
    for(int j = 5; j < 9; j++) {
      if(board[j] == c) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[5] == c) {
    for(int j = 6; j < 9; j++) {
      if(board[j] == c && j!= 7) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[6] == c) {
    for(int j = 7; j < 9; j++) {
      if(board[j] == c) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[7] == c) {
    for(int j = 8; j < 9; j++) {
      if(board[j] == c) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }

  //this section loses points for the player having corner

   if(board[0] == oc) {
    for(int j = 1; j < 9; j++) {
      if(board[j] == oc && j != 5 && j!= 7) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[1] == oc) {
    for(int j = 2; j < 9; j++) {
      if(board[j] == oc && j != 3 && j!= 5 && j!=6 && j!=8) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[2] == oc) {
    for(int j = 3; j < 9; j++) {
      if(board[j] == oc && j!= 7) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[3] == oc) {
    for(int j = 4; j < 9; j++) {
      if(board[j] == oc && j!= 7 && j!=8) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[4] == oc) {
    for(int j = 5; j < 9; j++) {
      if(board[j] == oc) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[5] == oc) {
    for(int j = 6; j < 9; j++) {
      if(board[j] == oc && j!= 7) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[6] == oc) {
    for(int j = 7; j < 9; j++) {
      if(board[j] == oc) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[7] == oc) {
    for(int j = 8; j < 9; j++) {
      if(board[j] == oc) {
        score -= TWO_PARTS_OF_A_WIN;
      }
    }
  }
  
  return score;
}

//changes a piece of the board based on input
void GameState::changeBoardPiece(Move move, Piece piece)
{
    //put players symbol in the give place
    board.at(move.board).at(move.square) = piece;

    //if the player won with that move, convert the cell tile
    //into an X or an O
    checkCellWon(move.board, piece);

    cellKnown = true;
    m_cell = move.square;

    bool flag = false;

    for (int i = 0; i < BOARD_SIZE; i++)
    {
        if (board.at(move.square).at(i) == PIECE_UNTAKEN) {
            flag = true;
        }
    }

    if (!flag) {
        cellKnown = false;
    }
    checkGameOver();
    lastMove = move;
}

void GameState::checkCellWon(int outerTile, Piece piece)
{
    bool won = false;
    //horizontal
    for(int i = 0; i < 3; i++)
    {
        if (board.at(outerTile).at(3*i) == board.at(outerTile).at(3*i+1)
            && board.at(outerTile).at(3*i) == board.at(outerTile).at(3*i+2)
            && (board.at(outerTile).at(3*i) != PIECE_UNTAKEN
            && board.at(outerTile).at(3*i) != PIECE_EMPTY)) {
            won = true;
        }
    }

    //vertical
    for(int i = 0; i < 3; i++)
    {
        if (board.at(outerTile).at(i) == board.at(outerTile).at(i+3)
            && board.at(outerTile).at(i) == board.at(outerTile).at(i+6)
            && (board.at(outerTile).at(i) != PIECE_UNTAKEN
            && board.at(outerTile).at(i) != PIECE_EMPTY)) {
            won = true;
        }
    }

    //diaganol
    if (board.at(outerTile).at(0) == board.at(outerTile).at(4)
        && board.at(outerTile).at(0) == board.at(outerTile).at(8)
        && (board.at(outerTile).at(0) != PIECE_UNTAKEN
        && board.at(outerTile).at(0) != PIECE_EMPTY)) {
        won = true;
    }

    if (board.at(outerTile).at(2) == board.at(outerTile).at(4)
        && board.at(outerTile).at(2) == board.at(outerTile).at(6)
        && (board.at(outerTile).at(2) != PIECE_UNTAKEN
        && board.at(outerTile).at(2) != PIECE_EMPTY)) {
        won = true;
    }

    if (won) {
        if (piece == PIECE_X) {
            board.at(outerTile) = CELL_X;
        } else {
            board.at(outerTile) = CELL_O;
        }
    }
}

void GameState::checkGameOver()
{
    bool won = false;

    //horizontal
    for(int i = 0; i < 3; i++)
    {
        if (board.at(3*i) == board.at(3*i+1) && board.at(3*i) == board.at(3*i+2)
            && (board.at(3*i) == CELL_X || board.at(3*i) == CELL_O)) {
            won = true;
        }
    }

    //vertical
    for(int i = 0; i < 3; i++)
    {
        if (board.at(i) == board.at(i+3) && board.at(i) == board.at(i+6)
            && (board.at(i) == CELL_X || board.at(i) == CELL_O)) {
            won = true;
        }
    }

    //diagnol
    if (board.at(0) == board.at(4) && board.at(0) == board.at(8)
        && (board.at(0) == CELL_X || board.at(0) == CELL_O)) {
        won = true;
    }

    if (board.at(2) == board.at(4) && board.at(2) == board.at(6)
        && (board.at(2) == CELL_X || board.at(2) == CELL_O)) {
        won = true;
    }

    if (won) {
        gameOver = true;
    }
}
