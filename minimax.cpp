#include "minimax.hpp"

#include <limits>
#include <stdexcept>

#include <omp.h>


namespace
{


const std::size_t NUM_THREADS = 2;


static int
negamax(const GameState &node, const std::size_t depth, int alpha, const int beta, const Piece piece)
{
    // at the bottom of the tree, evaluate their score
    if (depth == 0)
        return node.evaluateScore(piece);

    // get the children of this node
    const std::vector<GameState> children = node.getPotentialChildren();

    // if there are no children, just evaluate
    if (children.empty())
        return node.evaluateScore(piece);

    int best_value = std::numeric_limits<int>::min() + 1;

    // loop through the children
    omp_set_dynamic(0);
    omp_set_num_threads(NUM_THREADS);
#pragma omp parallel for num_threads(NUM_THREADS)
    for (std::size_t i = 0; i < children.size(); ++i) {
        if (alpha < beta) {
            const int v = -negamax(children.at(i), depth - 1, -beta, -alpha, piece);

            // update best_value to be the highest scoring child by the end of this loop
            best_value = std::max(best_value, v);
            alpha = std::max(alpha, v);
        }
    }

    return best_value;
}


}


Move
minimax(const GameState &node, std::size_t max_depth)
{
    // get the children
    const std::vector<GameState> children = node.getPotentialChildren();

    // variable for the optimal move
    std::pair<Move, int> candidate(Move(), std::numeric_limits<int>::min() + 1);

    // loop through all of this gamestates children
    for (std::vector<GameState>::const_iterator it = children.begin();
            it != children.end(); ++it) {
        // each child calls the min/max tree to get a score
        const int v = negamax(*it, max_depth, std::numeric_limits<int>::min() + 1,
                std::numeric_limits<int>::max() - 1, node.getTurn());

        // pick the highest score as the correct choice
        if (v > candidate.second) {
            candidate.second = v;
            candidate.first = it->lastMove;
        }
    }

    // if there was no move, there is an error (this function shouldn't have been called)
    if (candidate.second == std::numeric_limits<int>::min() + 1)
        throw std::logic_error("did not find any moves");

    return candidate.first;
}
