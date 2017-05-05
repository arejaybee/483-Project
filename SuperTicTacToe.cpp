#include "SuperTicTacToe.h"
using namespace std;

//Constructor
SuperTicTacToe::SuperTicTacToe() : game(* (new GameState()))
{
  //game = *(new GameState());
}

//plays the game
void SuperTicTacToe::play()
{
    //prints out the board
    printBoard();

    //keep playing until the game is over
    while (!game.gameOver) {
        //player goes first
        //getPlayerInput(PIECE_X);
        getInput(PIECE_X, USER);
        printBoard();
        game.checkGameOver();
        //cout << "Score: "<<game.evaluateScore(PIECE_X) << endl;
	
        //if the player won, game can end and tell them they won
        if (game.gameOver) {
            cout << "Player wins!" << endl;
        }
        //let the computer go
        else {
	  //getCompInput(PIECE_O);
	  /*cout<<"Is cell known? "<<game.cellKnown<<endl;
	   vector<Move> possibleMoves = game.getPotentialMoves();
            for (unsigned int i = 0; i < possibleMoves.size(); i++) {
                cout << "[" << possibleMoves[i].board << ", " << possibleMoves[i].square << "], ";
		}
		cout << endl;*/
            getInput(PIECE_O, TREE);
            game.checkGameOver();
	    cout<<"The computer will go to "<<game.lastMove.board<<" "<<game.lastMove.square<<endl;
            printBoard();
            //cout << "Score: "<<game.evaluateScore(PIECE_O) << endl;

            if (game.gameOver) {
                cout << "Computer wins!" << endl;
            }
        }
    }
}

//prints out the board to terminal
//idk what I am doing, but it looks ok!
void SuperTicTacToe::printBoard()
{
    game.printBoard();
}

//gets input from player
void SuperTicTacToe::getPlayerInput(Piece p)
{
    bool inputIsValid = false;
    Move m;
    m.board = -1; //cell
    m.square = -1; //space

    while (!inputIsValid) {
      //if we know where to send the player, dont ask them
        if (game.cellKnown) {
            cout << "You are in cell: " << game.m_cell << endl;
            cout << "Enter a space to play in: ";
            cin >> m.square;
            m.board = game.m_cell;
        }
	//ask where to send the player
        else {
            cout << "Enter a cell to play in followed by a space to play in: ";
            cin >> m.board;
            cin >> m.square;
        }
	vector<Move> temp = game.getPotentialMoves();
	inputIsValid = false; //just in case ;)
	for(unsigned int i = 0; i < temp.size(); i++)
	  {
	    if(temp[i].board == m.board && temp[i].square == m.square)
	      {
		inputIsValid = true;
		i = temp.size(); //poor man's break
	      }
	  }
	//if they could not pass easy validation, make them try again
        if (!inputIsValid) {
            cout << "Invalid!" << endl;
            m.board = -1;
            m.square = -1;
        }
    }
    //put their piece onto the board
    game.changeBoardPiece(m, p);

}

//gets computer input
void SuperTicTacToe::getCompInput(Piece p)
{
  vector<Move> g = game.getPotentialMoves();
  //cout<<"I can move to: "<<endl;
  for(unsigned int i = 0; i < g.size(); i++)
    {
      //cout<<g[i].board<<" , "<<g[i].square<<endl;
    }

  const Move myMove = minimax(game, 7);
  game.changeBoardPiece(myMove, p);
}

//gets random input
void SuperTicTacToe::getRandInput(Piece p)
{
    vector<Move> g = game.getPotentialMoves();
    int size = g.size();
    int selection = rand() % size;
    game.changeBoardPiece(g[selection], p);
}

void SuperTicTacToe::getInput(Piece p, moveType t)
{
    if (t == USER) {
        getPlayerInput(p);
    }
    else if (t == RANDOM) {
        getRandInput(p);
    }
    else if (t == TREE) {
        getCompInput(p);
    }
    else {}
}


