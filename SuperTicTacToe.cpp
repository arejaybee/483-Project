#include "SuperTicTacToe.h"
using namespace std;
//Constructor
SuperTicTacToe::SuperTicTacToe() :
    cellKnown(false),
    m_cell(-1),
    gameWon(false)
{
  for(int i = 0; i < BOARD_SIZE; i++)
    {
      board[i] = "---------";
    }
}

//plays the game
void SuperTicTacToe::play()
{
  //prints out the board
  printBoard();

  //keep playing until the game is over
  while(!gameWon)
    {
      //player goes first
      getPlayerInput();
      printBoard();
      checkGameOver();

      //if the player won, game can end and tell them they won
      if(gameWon)
	{
	  cout<<"Player wins!"<<endl;
	}
      //let the computer go
      else
	{
	  getCompInput();
	  checkGameOver();
	  printBoard();
	  if(gameWon)
	    {
	      cout<<"Computer wins!"<<endl;
	    }
	}
    }
}
  
//prints out the board to terminal
//idk what I am doing, but it looks ok!
void SuperTicTacToe::printBoard()
{
  cout<<" _____________________________\n\n";
  for(int i = 0; i < BOARD_SIZE; i+=3)
    {
      for(int j = 0; j < 3; j++)
	{
	  cout<<" || ";
	  for(int k = 0; k < 3; k++)
	    {	   
	      cout<<board[k+i][0+(j*3)]<<" "<<board[k+i][1+(j*3)]<<" "<<board[k+i][2+(j*3)]<<" ";
	      cout<<"|| ";
	    }
	  cout<<endl;
	}
      if(i%3 == 0)
	{
	  cout<<" _____________________________\n\n";
	}
    }
  cout<<endl<<endl;;
}

//gets input from player
void SuperTicTacToe::getPlayerInput()
{
  bool inputIsValid = false;
  int cell = -1;
  int space = -1;
  while(!inputIsValid)
    {
      if(cellKnown)
	{
	  cout<<"You are in cell: "<<m_cell<<endl;
	  cout<<"Enter a space to play in: ";
	  cin>>space;
	  cell = m_cell;
	}
      else
	{
	  cout<<"Enter a cell to play in followed by a space to play in: ";
	  cin>>cell;
	  cin>>space;
	}
      if(cell < 0 || cell > 9 || space < 0 || space > 9)
	{
	  inputIsValid = false;
	}
      else if(board[cell][space] == '-')
	{
	  inputIsValid = true;
	}

      if(!inputIsValid)
	{
	  cout<<"Invalid!"<<endl;
	  space = -1;
	  cell = -1;
	}
    }
  changeBoardPiece(cell,space, PIECE_X);
    
}

//gets computer input
void SuperTicTacToe::getCompInput()
{
  bool inputIsValid = false;
  int cell = -1;
  int space = -1;
  while(!inputIsValid)
    {
      if(cellKnown)
	{	
	  cell = m_cell;
	  
	  //picks a space number
	  for(int i = 0; i < BOARD_SIZE; i++)
	    {
	      if(board[m_cell][i] == '-')
		{
		  inputIsValid = true;
		  cell = m_cell;
		  space = i;
		}
	    }
	}
      else
	{
	  for(int i = 0; i< BOARD_SIZE; i++)
	    {
	      for(int j = 0; j < BOARD_SIZE; j++)
		{
		  if(board[i][j] == '-')
		    {
		      inputIsValid = true;
		      cell = i;
		      space = j;
		    }
		}
	    }
	}
    }
  changeBoardPiece(cell,space, PIECE_O);
}

void SuperTicTacToe::checkGameOver()
{
  bool won = false;
  //horizontal
  if(board[0] == board[1] && board[0] == board[2] && (board[0] == CELL_X || board[0] == CELL_O))
    {
      won = true;
    }
  if(board[3] == board[4] && board[3] == board[5] && (board[3] == CELL_X || board[3] == CELL_O))
    {
      won = true;
    }
  if(board[6] == board[7] && board[6] == board[8] && (board[6] == CELL_X || board[6] == CELL_O))
    {
      won = true;
    }

  //vertical
  if(board[0] == board[3] && board[0] == board[6] && (board[0] == CELL_X || board[0] == CELL_O))
    {
      won = true;
    }
  if(board[1] == board[4] && board[1] == board[7] && (board[1] == CELL_X || board[1] == CELL_O))
    {
      won = true;
    }
  if(board[2] == board[5] && board[2] == board[8] && (board[2] == CELL_X || board[2] == CELL_O))
    {
      won = true;
    }
  //diagnol
  if(board[0] == board[5] && board[0] == board[8] && (board[0] == CELL_X || board[0] == CELL_O))
    {
      won = true;
    }
  if(board[2] == board[5] && board[2] == board[7] && (board[0] == CELL_X || board[0] == CELL_O))
    {
      won = true;
    }
  if(won)
    {
      gameWon = true;
    }
}
void SuperTicTacToe::checkCellWon(int outerTile, Piece piece)
{
  bool won = false;
  //horizontal

  if(board[outerTile][0] == board[outerTile][1] && board[outerTile][0] == board[outerTile][2] && (board[outerTile][0] != '-' && board[outerTile][0] != ' '))
    {
      won = true;
    }
  if(board[outerTile][3] == board[outerTile][4] && board[outerTile][3] == board[outerTile][5] && (board[outerTile][3] != '-' && board[outerTile][3] != ' '))
    {
      won = true;
    }
  if(board[outerTile][6] == board[outerTile][7] && board[outerTile][6] == board[outerTile][8] && board[outerTile][6] != '-' && board[outerTile][6] != ' ')
    {
      won = true;
    }

  //vertical
  if(board[outerTile][0] == board[outerTile][3] && board[outerTile][0] == board[outerTile][6] && (board[outerTile][0] != '-' && board[outerTile][0] != ' '))
    {
      won = true;
    }
  if(board[outerTile][1] == board[outerTile][4] && board[outerTile][1] == board[outerTile][7] && (board[outerTile][1] != '-' && board[outerTile][1] != ' '))
    {
      won = true;
    }
  if(board[outerTile][2] == board[outerTile][5] && board[outerTile][2] == board[outerTile][8] && (board[outerTile][2] != '-' && board[outerTile][2] != ' '))
    {
      won = true;
    }

  //diaganol
  if(board[outerTile][0] == board[outerTile][4] && board[outerTile][0] == board[outerTile][8] && (board[outerTile][0] != '-' && board[outerTile][0] != ' '))
    {
      won = true;
    }
  if(board[outerTile][2] == board[outerTile][4] && board[outerTile][2] == board[outerTile][6] && (board[outerTile][2] != '-' && board[outerTile][2] != ' '))
    {
      won = true;
    }

  if(won)
    {
      if(piece == PIECE_X)
	{
	  board[outerTile] = CELL_X;
	}
      else
	{
	  board[outerTile] = CELL_O;
	}
    }  
}

//changes a piece of the board based on input
void SuperTicTacToe::changeBoardPiece(int outerTile, int innerTile, Piece piece)
{

  //put players symbol in the give place
  board[outerTile].at(innerTile) = piece;
  
  //if the player won with that move, convert the cell tile
  //into an X or an O
  checkCellWon(outerTile, piece);

  cellKnown = true;
  m_cell = innerTile;
  
  bool flag = false;
  for(int i = 0; i < BOARD_SIZE; i++)
    {
      if(board[innerTile][i] == '-')
	{
	  flag = true;
	}
    }
  if(!flag)
    {
      cellKnown = false;
    }
}
