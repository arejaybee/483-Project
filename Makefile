all:
	g++ -ansi -Werror -pedantic -Wall -Wextra -Weffc++ -Wshadow GameState.cpp SuperTicTacToe.cpp Driver.cpp minimax.cpp -o player.out
run: all
	./player.out
