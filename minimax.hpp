#ifndef MINIMAX_HPP
#define MINIMAX_HPP


#include <cstddef>


class MinimaxState
{
public:
  //deconstructor
  virtual ~MinimaxState();
  
  //the value of a node
  virtual int get_node_score() const = 0;
  //number of children a node has
  virtual std::size_t get_child_count() const = 0;
  
  //should return a child node given some index
  virtual MinimaxState &get_child(std::size_t index) = 0;
};

const MinimaxState &minimax_evaluate(MinimaxState &head);

#endif
