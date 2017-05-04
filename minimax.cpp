#include "minimax.hpp"

#include <limits>


namespace
{


static int
minimax_evaluate(const GameState &node, const std::size_t depth, int alpha,
		 int beta)
{
    if (depth == 0)
	return node.evaluateScore();

    const std::vector<Move> moves = node.getPotentialMoves();

    if (moves.empty())
	return node.evaluateScore();

    const Piece turn = node.getTurn();

    if (turn == PIECE_X) {
	int v = std::numeric_limits<int>::min();

	for (std::vector<Move>::const_iterator it = moves.begin(); it != moves.end();
	     ++it) {
	    GameState child = node;
	    child.changeBoardPiece(*it, turn);
	    v = std::max(v, minimax_evaluate(child, depth - 1, alpha, beta));
	    alpha = std::max(alpha, v);

	    if (beta <= alpha)
		break;
	}

	return v;
    } else {
	int v = std::numeric_limits<int>::min();

	for (std::vector<Move>::const_iterator it = moves.begin(); it != moves.end();
	     ++it) {
	    GameState child = node;
	    child.changeBoardPiece(*it, turn);
	    v = std::min(v, minimax_evaluate(child, depth - 1, alpha, beta));
	    beta = std::min(beta, v);

	    if (beta <= alpha)
		break;
	}

	return v;
    }
}


}


std::size_t
minimax(const GameState &node, std::size_t max_depth)
{
    const Piece turn = node.getTurn();
    const std::vector<Move> moves = node.getPotentialMoves();
    std::pair<std::size_t, int> candidate(0, std::numeric_limits<int>::min());

    if (turn == PIECE_O)
	candidate.second = -candidate.second;

    for (std::vector<Move>::const_iterator it = moves.begin(); it != moves.end();
	 ++it) {
	GameState child = node;
	child.changeBoardPiece(*it, node.getTurn());
	const int v = minimax_evaluate(child, max_depth - 1,
				       std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

	if (turn == PIECE_X && v > candidate.second)
	    candidate = std::make_pair(std::distance(moves.begin(), it), v);
	else if (turn == PIECE_O && v < candidate.second)
	    candidate = std::make_pair(std::distance(moves.begin(), it), v);
    }

    return candidate.first;
}
