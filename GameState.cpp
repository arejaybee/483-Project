#include "GameState.h"

using namespace std;

GameState::GameState() : board(BOARD_SIZE)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.at(i) = "---------";
    }
}

void GameState::printBoard()
{
    cout << " _____________________________\n\n";

    for (int i = 0; i < BOARD_SIZE; i += 3) {
        for (int j = 0; j < 3; j++) {
            cout << " || ";

            for (int k = 0; k < 3; k++) {
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

    for (int i = 0; i < BOARD_SIZE; i++) {
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
	if (board.at(3*i) == board.at(3*i+1) && board.at(o) == board.at(3*i+2)
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
