#ifndef TICTACTREE_HPP
#define TICTACTREE_HPP


#include <utility>


class TicTacTree : MinimaxState
{
public:
  enum Player {PLAYER_MIN, PLAYER_MAX};

  TicTacTree(Player layer, string[] boardState);
  // deconstructor
  ~MinimaxState();
  
  // the player at a node
  Player get_player() const;
  
  // the value of a node
  int get_node_score() const;
  
  // number of children a node has
  std::size_t get_child_count() const;
  
  // should return a child node given some index
  MinimaxState &get_child(std::size_t index);

private:
  Player m_layer;
  int m_score;
  size_t m_numChildren;
  MinimaxState[] m_children;
};


// returns <index of optimal child, score>
std::pair<std::size_t, int> minimax_evaluate(MinimaxState &head);


#endif
