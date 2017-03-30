#include "SuperTicTacToe.h"
using namespace std;

//Constructor
SuperTicTacToe::SuperTicTacToe() :
    board(BOARD_SIZE),
    cellKnown(false),
    m_cell(-1),
    gameWon(false)
{
    for (int i = 0; i < BOARD_SIZE; i++) {
        board.at(i) = "---------";
    }
}

//plays the game
void SuperTicTacToe::play()
{
    //prints out the board
    printBoard();

    //keep playing until the game is over
    while (!gameWon) {
        //player goes first
        getPlayerInput();
        printBoard();
        checkGameOver();

        //if the player won, game can end and tell them they won
        if (gameWon) {
            cout << "Player wins!" << endl;
        }
        //let the computer go
        else {
            getCompInput();
            checkGameOver();
            printBoard();

            if (gameWon) {
                cout << "Computer wins!" << endl;
            }
        }
    }
}

//prints out the board to terminal
//idk what I am doing, but it looks ok!
void SuperTicTacToe::printBoard()
{
    cout << " _____________________________\n\n";

    for (int i = 0; i < BOARD_SIZE; i += 3) {
        for (int j = 0; j < 3; j++) {
            cout << " || ";

            for (int k = 0; k < 3; k++) {
                cout << board.at(k + i).at(0 + (j * 3)) << " " << board.at(k + i).at(1 +
                        (j * 3)) << " " << board.at(k + i).at(2 + (j * 3)) << " ";
                cout << "|| ";
            }

            cout << endl;
        }

        if (i % 3 == 0) {
            cout << " _____________________________\n\n";
        }
    }

    cout << endl << endl;;
}

//gets input from player
void SuperTicTacToe::getPlayerInput()
{
    bool inputIsValid = false;
    int cell = -1;
    int space = -1;

    while (!inputIsValid) {
        if (cellKnown) {
            cout << "You are in cell: " << m_cell << endl;
            cout << "Enter a space to play in: ";
            cin >> space;
            cell = m_cell;
        } else {
            cout << "Enter a cell to play in followed by a space to play in: ";
            cin >> cell;
            cin >> space;
        }

        if (cell < 0 || cell > 9 || space < 0 || space > 9) {
            inputIsValid = false;
        } else if (board.at(cell).at(space) == '-') {
            inputIsValid = true;
        }

        if (!inputIsValid) {
            cout << "Invalid!" << endl;
            space = -1;
            cell = -1;
        }
    }

    changeBoardPiece(cell, space, PIECE_X);

}

//gets computer input
void SuperTicTacToe::getCompInput()
{
    bool inputIsValid = false;
    int cell = -1;
    int space = -1;

    while (!inputIsValid) {
        if (cellKnown) {
            cell = m_cell;

            //picks a space number
            for (int i = 0; i < BOARD_SIZE; i++) {
                if (board.at(m_cell).at(i) == '-') {
                    inputIsValid = true;
                    cell = m_cell;
                    space = i;
                }
            }
        } else {
            for (int i = 0; i < BOARD_SIZE; i++) {
                for (int j = 0; j < BOARD_SIZE; j++) {
                    if (board.at(i).at(j) == '-') {
                        inputIsValid = true;
                        cell = i;
                        space = j;
                    }
                }
            }
        }
    }

    changeBoardPiece(cell, space, PIECE_O);
}

void SuperTicTacToe::checkGameOver()
{
    bool won = false;

    //horizontal
    if (board.at(0) == board.at(1) && board.at(0) == board.at(2)
            && (board.at(0) == CELL_X || board.at(0) == CELL_O)) {
        won = true;
    }

    if (board.at(3) == board.at(4) && board.at(3) == board.at(5)
            && (board.at(3) == CELL_X || board.at(3) == CELL_O)) {
        won = true;
    }

    if (board.at(6) == board.at(7) && board.at(6) == board.at(8)
            && (board.at(6) == CELL_X || board.at(6) == CELL_O)) {
        won = true;
    }

    //vertical
    if (board.at(0) == board.at(3) && board.at(0) == board.at(6)
            && (board.at(0) == CELL_X || board.at(0) == CELL_O)) {
        won = true;
    }

    if (board.at(1) == board.at(4) && board.at(1) == board.at(7)
            && (board.at(1) == CELL_X || board.at(1) == CELL_O)) {
        won = true;
    }

    if (board.at(2) == board.at(5) && board.at(2) == board.at(8)
            && (board.at(2) == CELL_X || board.at(2) == CELL_O)) {
        won = true;
    }

    //diagnol
    if (board.at(0) == board.at(5) && board.at(0) == board.at(8)
            && (board.at(0) == CELL_X || board.at(0) == CELL_O)) {
        won = true;
    }

    if (board.at(2) == board.at(5) && board.at(2) == board.at(7)
            && (board.at(0) == CELL_X || board.at(0) == CELL_O)) {
        won = true;
    }

    if (won) {
        gameWon = true;
    }
}
void SuperTicTacToe::checkCellWon(int outerTile, Piece piece)
{
    bool won = false;
    //horizontal

    if (board.at(outerTile).at(0) == board.at(outerTile).at(1)
            && board.at(outerTile).at(0) == board.at(outerTile).at(2)
            && (board.at(outerTile).at(0) != '-' && board.at(outerTile).at(0) != ' ')) {
        won = true;
    }

    if (board.at(outerTile).at(3) == board.at(outerTile).at(4)
            && board.at(outerTile).at(3) == board.at(outerTile).at(5)
            && (board.at(outerTile).at(3) != '-' && board.at(outerTile).at(3) != ' ')) {
        won = true;
    }

    if (board.at(outerTile).at(6) == board.at(outerTile).at(7)
            && board.at(outerTile).at(6) == board.at(outerTile).at(8)
            && board.at(outerTile).at(6) != '-' && board.at(outerTile).at(6) != ' ') {
        won = true;
    }

    //vertical
    if (board.at(outerTile).at(0) == board.at(outerTile).at(3)
            && board.at(outerTile).at(0) == board.at(outerTile).at(6)
            && (board.at(outerTile).at(0) != '-' && board.at(outerTile).at(0) != ' ')) {
        won = true;
    }

    if (board.at(outerTile).at(1) == board.at(outerTile).at(4)
            && board.at(outerTile).at(1) == board.at(outerTile).at(7)
            && (board.at(outerTile).at(1) != '-' && board.at(outerTile).at(1) != ' ')) {
        won = true;
    }

    if (board.at(outerTile).at(2) == board.at(outerTile).at(5)
            && board.at(outerTile).at(2) == board.at(outerTile).at(8)
            && (board.at(outerTile).at(2) != '-' && board.at(outerTile).at(2) != ' ')) {
        won = true;
    }

    //diaganol
    if (board.at(outerTile).at(0) == board.at(outerTile).at(4)
            && board.at(outerTile).at(0) == board.at(outerTile).at(8)
            && (board.at(outerTile).at(0) != '-' && board.at(outerTile).at(0) != ' ')) {
        won = true;
    }

    if (board.at(outerTile).at(2) == board.at(outerTile).at(4)
            && board.at(outerTile).at(2) == board.at(outerTile).at(6)
            && (board.at(outerTile).at(2) != '-' && board.at(outerTile).at(2) != ' ')) {
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

//changes a piece of the board based on input
void SuperTicTacToe::changeBoardPiece(int outerTile, int innerTile, Piece piece)
{

    //put players symbol in the give place
    board.at(outerTile).at(innerTile) = piece;

    //if the player won with that move, convert the cell tile
    //into an X or an O
    checkCellWon(outerTile, piece);

    cellKnown = true;
    m_cell = innerTile;

    bool flag = false;

    for (int i = 0; i < BOARD_SIZE; i++) {
        if (board.at(innerTile).at(i) == '-') {
            flag = true;
        }
    }

    if (!flag) {
        cellKnown = false;
    }
}
