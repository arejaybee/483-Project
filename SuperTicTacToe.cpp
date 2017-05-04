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
        getPlayerInput();
        printBoard();
        game.checkGameOver();

        //if the player won, game can end and tell them they won
        if (game.gameOver) {
            cout << "Player wins!" << endl;
        }
        //let the computer go
        else {
            getCompInput();
            game.checkGameOver();
            printBoard();
            cout << game.evaluateScore() << endl;

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
void SuperTicTacToe::getPlayerInput()
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
    game.changeBoardPiece(m, PIECE_X);

}

//gets computer input
void SuperTicTacToe::getCompInput()
{
    /*
    bool inputIsValid = false;
    Move m;
    m.board = -1; //cell
    m.square = -1; //space
    while (!inputIsValid) {
        if (game.cellKnown) {
            m.board = game.m_cell;

            //picks a space number
            for (int i = 0; i < BOARD_SIZE; i++) {
                m.board = game.m_cell;
                m.square = i;
                if (game.charAt(m) == '-') {
                    inputIsValid = true;
                    m.board = game.m_cell;
                    m.square = i;
		    //end the for loop
                    i = BOARD_SIZE;
                }
            }
        }
        else {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    m.board = i;
                    m.square = j;
		    if (game.charAt(m) == '-') {
                        inputIsValid = true;
                        m.board = i;
                        m.square = j;
			//end the for loop
                        i = BOARD_SIZE;
                        j = BOARD_SIZE;
                    }
                }
            }
        }
    }
    game.changeBoardPiece(m, PIECE_O);
    */
  /*    vector<Move> g = game.getPotentialMoves();
    int size = g.size();
    int selection = rand() % size;
    game.changeBoardPiece(g[selection], PIECE_O);*/
  const Move myMove = minimax(game, 4);
  game.changeBoardPiece(myMove,PIECE_O);
}




