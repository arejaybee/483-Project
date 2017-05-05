#include "minimax.hpp"

#include <limits>
#include <stdexcept>


namespace
{


static int
negamax(const GameState &node, const std::size_t depth, int alpha, int beta, const bool my_turn)
{
    const int color = my_turn ? 1 : -1;

    if (depth == 0)
        return color * node.evaluateScore(node.getTurn());

    const std::vector<GameState> children = node.getPotentialChildren();

    if (children.empty())
        return color * node.evaluateScore(node.getTurn());

    int best_value = std::numeric_limits<int>::min() + 1;

    for (std::vector<GameState>::const_iterator it = children.begin(); it != children.end(); ++it) {
        const int v = -negamax(*it, depth - 1, -beta, -alpha, !my_turn);

        best_value = std::max(best_value, v);
        alpha = std::max(alpha, v);

        if (alpha >= beta)
            break;
    }

    return best_value;
}


}


Move
minimax(const GameState &node, std::size_t max_depth)
{
    // get the children
    const std::vector<GameState> children = node.getPotentialChildren();

    std::pair<Move, int> candidate(Move(), std::numeric_limits<int>::min() + 1);

    for (std::vector<GameState>::const_iterator it = children.begin(); it != children.end(); ++it) {
        const int v = negamax(*it, max_depth, std::numeric_limits<int>::min() + 1, std::numeric_limits<int>::max() - 1, true);

        if (v > candidate.second) {
            candidate.second = v;
            candidate.first = it->lastMove;
        }
    }

    if (candidate.second == std::numeric_limits<int>::min() + 1)
        throw std::logic_error("did not find any moves");

    return candidate.first;
}
