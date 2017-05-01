#include "minimax.hpp"

#include <limits>
#include <stdexcept>


MinimaxState::~MinimaxState()
{
}


std::pair<std::size_t, int> minimax_evaluate(MinimaxState &head)
{
    // currently implements a very basic Minimax function (recursive; no pruning)

    const std::size_t child_count = head.get_child_count();

    if (child_count == 0)
      {
	throw std::invalid_argument("head is a leaf");
      }

    std::pair<std::size_t, int> result(0, 0);

    //check all children of the node
    for (std::size_t i = 0; i < child_count; ++i) 
      {
	MinimaxState &child = head.get_child(i);
	int candidate;
	
	//if there are no children, calculate the score
	if (child.get_child_count() == 0){
	    candidate = child.get_node_score();
	  }
	//otherwize recurse down(im not sure what second is?)
	else{
	    candidate = minimax_evaluate(child).second;
	  }
	//if the first iteration of loop, assume it is the result
	if (i == 0) {
	    result.first = i;
	    result.second = candidate;
	  }
	//if we are looking for the min
	if (head.get_player() == MinimaxState::PLAYER_MIN) {
	  //see if the current node's number is less than the result
	  //if so, replace
	    if (candidate < result.second) {
	      result.first = i;
	      result.second = candidate;
	    }
	  } 
	//otherwise do the same for the max
	else if (candidate > result.second) {
	  result.first = i;
	  result.second = candidate;
	}
    }

    return result;
}
