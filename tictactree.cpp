#include <tictactree.hpp>

TicTacTree::TicTacTree(Player layer, string[] gameState, size_t numChildren)
{
  m_layer = layer;
  m_numChildren = numChildren;
  string[] m_gameState = gameState;
}

Player TicTacTree::get_player()const
{
  return m_layer;
}

int TicTacTree::get_node_score()const
{
  return m_score;
}

std::size_t TicTacTree::get_child_count()const
{
  return m_numChildren;
}

MinimaxState TicTacTree::&get_child(std::size_t index)
{
  return m_children[index];
}
