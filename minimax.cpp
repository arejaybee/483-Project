#include "minimax.hpp"

#include <limits>
#include <stdexcept>


MinimaxState::~MinimaxState()
{
}


std::pair<std::size_t, int>
minimax_evaluate(MinimaxState &head)
{
    // currently implements a very basic Minimax function (recursive; no pruning)

    const std::size_t child_count = head.get_child_count();

    if (child_count == 0)
	throw std::invalid_argument("head is a leaf");

    std::pair<std::size_t, int> result(0, 0);

    for (std::size_t i = 0; i < child_count; ++i) {
	MinimaxState &child = head.get_child(i);
	int candidate;

	if (child.get_child_count() == 0)
	    candidate = child.get_node_score();
	else
	    candidate = minimax_evaluate(child).second;

	if (i == 0) {
	    result.first = i;
	    result.second = candidate;
	}

	if (head.get_player() == MinimaxState::PLAYER_MIN) {
	    if (candidate < result.second) {
		result.first = i;
		result.second = candidate;
	    }
	} else if (candidate > result.second) {
	    result.first = i;
	    result.second = candidate;
	}
    }

    return result;
}
