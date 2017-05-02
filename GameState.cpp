#include "GameState.h"

using namespace std;

GameState::GameState() : gameOver(false) , cellKnown(false) , m_cell(-1) , board(BOARD_SIZE) , lastMove(Move()) 
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        board.at(i) = "---------";
    }
}

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

int GameState::evaluateScore()
{
  int score = 0;
  
  for(int i = 0; i < BOARD_SIZE; i++)
    {
      //for winning any board, you get 5 points
      if(board[i] == CELL_O)
	{
	  score += SMALL_BOARD_WIN;
	}

      //if 2/3 squares are O, you get 4 points for getting close to winning
      if(board[i][0] == 'O')
	{
	  for(int j = 1; j < 9; j++)
	    {
	      if(board[i][j] == 'O' && j != 5 && j!= 7)
		{
		  score+=4;
		}
	    }
	}

      if(board[i][1] == 'O')
	{
	  for(int j = 2; j < 9; j++)
	    {
	      if(board[i][j] == 'O' && j != 3 && j!= 5 && j!=6 && j!=8)
		{
		  score+=4;
		}
	    }
	}

      if(board[i][2] == 'O')
	{
	  for(int j = 3; j < 9; j++)
	    {
	      if(board[i][j] == 'O' && j!= 7)
		{
		  score+=4;
		}
	    }
	}
      if(board[i][3] == 'O')
	{
	  for(int j = 4; j < 9; j++)
	    {
	      if(board[i][j] == 'O' && j!= 7 && j!=8)
		{
		  score+=4;
		}
	    }
	}
      if(board[i][4] == 'O')
	{
	  for(int j = 5; j < 9; j++)
	    {
	      if(board[i][j] == 'O')
		{
		  score+=4;
		}
	    }
	}
      if(board[i][5] == 'O')
	{
	  for(int j = 6; j < 9; j++)
	    {
	      if(board[i][j] == 'O' && j!= 7)
		{
		  score+=4;
		}
	    }
	}
      if(board[i][6] == 'O')
	{
	  for(int j = 7; j < 9; j++)
	    {
	      if(board[i][j] == 'O')
		{
		  score+=4;
		}
	    }
	}
      if(board[i][7] == 'O')
	{
	  for(int j = 8; j < 9; j++)
	    {
	      if(board[i][j] == 'O')
		{
		  score+=4;
		}
	    }
	}
      
      //if the center is an O you get an additional 3 points
      if(board[i][4] == 'O')
	{
	  score += SQUARE_IN_CENTER_BOARD;
	}
    }
  //winning the center board is an additional 10 points
  if(board[4] == CELL_O)
    {
      score += MIDDLE_BOARD_WIN;
    }
  //winning a corner is an additional 3 points
  if(board[0] == CELL_O || board[2] == CELL_O || board[6] == CELL_O || board[8] == CELL_O)
    {
      score += CORNER_BOARD_WIN;
    }

  //if you have 2/3 parts needed to win, thats 4 points
  
  if(board[0] == CELL_O)
    {
      for(int j = 1; j < 9; j++)
	{
	  if(board[j] == CELL_O && j != 5 && j!= 7)
	    {
	      score+=4;
	    }
	}
    }
  
  if(board[1] == CELL_O)
    {
      for(int j = 2; j < 9; j++)
	{
	  if(board[j] == CELL_O && j != 3 && j!= 5 && j!=6 && j!=8)
	    {
	      score+=4;
	    }
	}
    }
  
  if(board[2] == CELL_O)
    {
      for(int j = 3; j < 9; j++)
	{
	  if(board[j] == CELL_O && j!= 7)
	    {
	      score+=4;
	    }
	}
    }
  if(board[3] == CELL_O)
    {
      for(int j = 4; j < 9; j++)
	{
	  if(board[j] == CELL_O && j!= 7 && j!=8)
	    {
	      score+=4;
	    }
	}
    }
  if(board[4] == CELL_O)
    {
      for(int j = 5; j < 9; j++)
	{
	  if(board[j] == CELL_O)
	    {
	      score+=4;
	    }
	}
    }
  if(board[5] == CELL_O)
    {
      for(int j = 6; j < 9; j++)
	{
	  if(board[j] == CELL_O && j!= 7)
	    {
		  score+=4;
	    }
	}
    }
  if(board[6] == CELL_O)
    {
      for(int j = 7; j < 9; j++)
	{
	  if(board[j] == CELL_O)
	    {
	      score+=4;
	    }
	}
    }
  if(board[7] == CELL_O)
    {
      for(int j = 8; j < 9; j++)
	{
	  if(board[j] == CELL_O)
	    {
	      score+=4;
	    }
	}
    }
  
  return score;
}

char GameState::charAt(Move m) {
    return board.at(m.board).at(m.square);
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
        if (board.at(move.square).at(i) == '-') {
            flag = true;
        }
    }

    if (!flag) {
        cellKnown = false;
    }
}

void GameState::checkCellWon(int outerTile, Piece piece)
{
    bool won = false;
    //horizontal
    for(int i = 0; i < 3; i++)
    {
        if (board.at(outerTile).at(3*i) == board.at(outerTile).at(3*i+1)
            && board.at(outerTile).at(3*i) == board.at(outerTile).at(3*i+2)
            && (board.at(outerTile).at(3*i) != '-'
            && board.at(outerTile).at(3*i) != ' ')) {
            won = true;
        }
    }

    //vertical
    for(int i = 0; i < 3; i++)
    {
        if (board.at(outerTile).at(i) == board.at(outerTile).at(i+3)
            && board.at(outerTile).at(i) == board.at(outerTile).at(i+6)
            && (board.at(outerTile).at(i) != '-'
            && board.at(outerTile).at(i) != ' ')) {
            won = true;
        }
    }

    //diaganol
    if (board.at(outerTile).at(0) == board.at(outerTile).at(4)
        && board.at(outerTile).at(0) == board.at(outerTile).at(8)
        && (board.at(outerTile).at(0) != '-'
        && board.at(outerTile).at(0) != ' ')) {
        won = true;
    }

    if (board.at(outerTile).at(2) == board.at(outerTile).at(4)
        && board.at(outerTile).at(2) == board.at(outerTile).at(6)
        && (board.at(outerTile).at(2) != '-'
        && board.at(outerTile).at(2) != ' ')) {
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
