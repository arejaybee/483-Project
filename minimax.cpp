#include "minimax.hpp"

#include <limits>


namespace
{


static int
minimax_evaluate(const GameState &node, const std::size_t depth, int alpha,
        int beta)
{
  //if we hit the bottom of the tree, evaluate the score
    if (depth == 0)
        return node.evaluateScore(PIECE_O);
    //get the children from this state
    const std::vector<GameState> children = node.getPotentialChildren();

    //if there are no children, this is a terminal node
    if (children.empty())
        return node.evaluateScore(PIECE_O);

    //whos turn is it?
    const Piece turn = node.getTurn();

    //if it is the player's turn, minimize
    if (turn == PIECE_X) {
        int v = std::numeric_limits<int>::max();

        for (std::vector<GameState>::const_iterator it = children.begin();
                it != children.end(); ++it) {
            v = std::min(v, minimax_evaluate(*it, depth - 1, alpha, beta));
            alpha = std::min(alpha, v);

            if (beta <= alpha)
                break;
        }

        return v;
    }
    //it is the AI's turn, maximize
    else {
        int v = std::numeric_limits<int>::max();

        for (std::vector<GameState>::const_iterator it = children.begin();
                it != children.end(); ++it) {
            v = std::min(v, minimax_evaluate(*it, depth - 1, alpha, beta));
            beta = std::max(beta, v);

            if (beta <= alpha)
                break;
        }

        return v;
    }
}


}


Move
minimax(const GameState &node, std::size_t max_depth)
{
  //whos turn is it?
    const Piece turn = node.getTurn();
    //get the children
    const std::vector<GameState> children = node.getPotentialChildren();
    std::pair<Move, int> candidate(Move(), std::numeric_limits<int>::max());

    if (turn == PIECE_O)
        candidate.second = std::numeric_limits<int>::min();

    for (std::vector<GameState>::const_iterator it = children.begin(); it != children.end(); ++it) {
        const int v = minimax_evaluate(*it, max_depth - 1, std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

        if (turn == PIECE_X && v < candidate.second)
            candidate = std::make_pair(it->lastMove, v);
        else if (turn == PIECE_O && v > candidate.second)
            candidate = std::make_pair(it->lastMove, v);
    }

    return candidate.first;
}
