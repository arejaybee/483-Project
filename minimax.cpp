#include "minimax.hpp"

#include <limits>
#include <stdexcept>


MinimaxState::~MinimaxState()
{
}


// currently implements a very basic Minimax function (recursive; no pruning)
std::pair<std::size_t, int> minimax_evaluate(MinimaxState &head)
{
  const std::size_t child_count = head.get_child_count();
  std::pair<std::size_t, int> result(0, 0);
  
  if (child_count == 0) {
    throw std::invalid_argument("head is a leaf");
  }
  
  for (std::size_t i = 0; i < child_count; ++i) { //check all children of the node
    MinimaxState &child = head.get_child(i);
    int candidate;
    
    if (child.get_child_count() == 0) { //if there are no children, calculate the score
      candidate = child.get_node_score();
    }
    else { //otherwize recurse down
      candidate = minimax_evaluate(child).second;
    }
    
    if (i == 0) { //if the first iteration of loop, assume it is the result
      result.first = i;
      result.second = candidate;
    }
    
    if (head.get_player() == MinimaxState::PLAYER_MIN) { //if we are looking for the min
      if (candidate < result.second) { //see if the current node's number is less than the result. if so, replace
        result.first = i;
        result.second = candidate;
      }
    }
    else if (candidate > result.second) { //otherwise do the same for the max
      result.first = i;
      result.second = candidate;
    }
  }
  return result;
}
