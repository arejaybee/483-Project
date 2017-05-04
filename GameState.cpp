#include "GameState.h"

using namespace std;

GameState::GameState() : gameOver(false) , cellKnown(false) , m_cell(-1) , board(BOARD_SIZE) , lastMove(Move()) 
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board.at(i) = "---------";
    }
}

GameState::GameState(GameState *g) : gameOver(false) , cellKnown(false) , m_cell(-1) , board(BOARD_SIZE) , lastMove(Move()) 
{
  gameOver = g->gameOver;
  cellKnown = g->cellKnown;
  m_cell = g->m_cell;
  board = g->board;
  lastMove = g->lastMove;
}

//This is witchcraft
void GameState::printBoard()
{
    cout << " _____________________________\n\n";

    for (int i = 0; i < BOARD_SIZE; i += 3)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << " || ";

            for (int k = 0; k < 3; k++)
            {
                cout << board.at(k + i).at(0 + (j * 3)) << " " <<
                        board.at(k + i).at(1 + (j * 3)) << " " <<
                        board.at(k + i).at(2 + (j * 3)) << " ";
                cout << "|| ";
            }

            cout << endl;
        }

        if (i % 3 == 0) {
            cout << " _____________________________\n\n";
        }
    }

    cout << endl << endl;
}

//just see if there is a char at the move option provided
char GameState::charAt(Move m)
{
    return board.at(m.board).at(m.square);
}

//a vector of places a player CAN move to
vector<Move> GameState::getPotentialMoves()
{
  vector<Move> potentialMoves;
  Move tempMove;

  if (cellKnown) {
    tempMove.board = lastMove.square;
    for (int i = 0; i < BOARD_SIZE; i++) {
      if (board[lastMove.square][i] == PIECE_UNTAKEN) {
        tempMove.square = i;
        potentialMoves.push_back(tempMove);
      }
    }
  }
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

vector<GameState> GameState::getPotentialChildren()
{
  vector<GameState> children;

  vector<Move> possibleMoves = getPotentialMoves();
  int numPossibleMoves = possibleMoves.size();

  for (int i = 0; i < numPossibleMoves; i++) {
    cout << possibleMoves[i].board << ", " << possibleMoves[i].square << endl;
    GameState tempGameState = GameState(*this);
    tempGameState.changeBoardPiece(possibleMoves[i], getTurn());
    children.push_back(tempGameState);
  }

  return children;
}

Piece GameState::getTurn() {
  if (board[lastMove.board][lastMove.square] == PIECE_X) {
    return PIECE_O;
  }
  else if (board[lastMove.board][lastMove.square] == PIECE_O) {
    return PIECE_X;
  }
  else {
    return PIECE_EMPTY;
  }
}

int GameState::evaluateScore()
{
  int score = 0;
  
  for(int i = 0; i < BOARD_SIZE; i++) {
    //for winning any board, you get SMALL_BOARD_WIN points
    if(board[i] == CELL_O) {
      score += SMALL_BOARD_WIN;
    }

    //if 2/3 squares are PIECE_O, you get TWO_PARTS_OF_A_BOARD points
    if(board[i][0] == PIECE_O) {
      for(int j = 1; j < 9; j++) {
        if(board[i][j] == PIECE_O && j != 5 && j!= 7) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][1] == PIECE_O) {
      for(int j = 2; j < 9; j++) {
        if(board[i][j] == PIECE_O && j != 3 && j!= 5 && j!=6 && j!=8) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][2] == PIECE_O) {
      for(int j = 3; j < 9; j++) {
        if(board[i][j] == PIECE_O && j!= 7) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][3] == PIECE_O) {
      for(int j = 4; j < 9; j++) {
        if(board[i][j] == PIECE_O && j!= 7 && j!=8) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][4] == PIECE_O) {
      for(int j = 5; j < 9; j++) {
        if(board[i][j] == PIECE_O) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][5] == PIECE_O) {
      for(int j = 6; j < 9; j++) {
        if(board[i][j] == PIECE_O && j!= 7) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][6] == PIECE_O) {
      for(int j = 7; j < 9; j++) {
        if(board[i][j] == PIECE_O) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    if(board[i][7] == PIECE_O) {
      for(int j = 8; j < 9; j++) {
        if(board[i][j] == PIECE_O) {
          score += TWO_PARTS_OF_A_BOARD;
        }
      }
    }
    
    //if the center is an O you get an additional CENTER_SQUARE_IN_SMALL_BOARD points
    if(board[i][4] == PIECE_O) {
      score += CENTER_SQUARE_IN_SMALL_BOARD;
    }
  }

  //gain SQUARE_IN_CENTER_BOARD points for every square you own in the center board
  for (int i = 0; i < BOARD_SIZE; i++) {
    if (board[4][i] == PIECE_O) {
      score += SQUARE_IN_CENTER_BOARD;
    }
  }

  //winning the center board is an additional MIDDLE_BOARD_WIN points
  if(board[4] == CELL_O) {
    score += MIDDLE_BOARD_WIN;
  }
  
  //winning a corner is an additional CORNER_BOARD_WIN points
  if(board[0] == CELL_O || board[2] == CELL_O || board[6] == CELL_O || board[8] == CELL_O) {
    score += CORNER_BOARD_WIN;
  }
  
  //if you have 2/3 parts needed to win, thats TWO_PARTS_OF_A_WIN points
  if(board[0] == CELL_O) {
    for(int j = 1; j < 9; j++) {
      if(board[j] == CELL_O && j != 5 && j!= 7) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[1] == CELL_O) {
    for(int j = 2; j < 9; j++) {
      if(board[j] == CELL_O && j != 3 && j!= 5 && j!=6 && j!=8) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[2] == CELL_O) {
    for(int j = 3; j < 9; j++) {
      if(board[j] == CELL_O && j!= 7) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[3] == CELL_O) {
    for(int j = 4; j < 9; j++) {
      if(board[j] == CELL_O && j!= 7 && j!=8) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[4] == CELL_O) {
    for(int j = 5; j < 9; j++) {
      if(board[j] == CELL_O) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[5] == CELL_O) {
    for(int j = 6; j < 9; j++) {
      if(board[j] == CELL_O && j!= 7) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[6] == CELL_O) {
    for(int j = 7; j < 9; j++) {
      if(board[j] == CELL_O) {
        score += TWO_PARTS_OF_A_WIN;
      }
    }
  }
  if(board[7] == CELL_O) {
    for(int j = 8; j < 9; j++) {
      if(board[j] == CELL_O) {
        score += TWO_PARTS_OF_A_WIN;
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

    if (board.at(2) == board.at(4) && board.at(2) == board.at(7)
        && (board.at(0) == CELL_X || board.at(0) == CELL_O)) {
        won = true;
    }

    if (won) {
        gameOver = true;
    }
}
