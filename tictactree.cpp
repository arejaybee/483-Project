#include <tictactree.hpp>

TicTacTree::TicTacTree(Player layer, string[] gameState)
{
  m_layer = layer;
}

Player TicTacTree::get_player()const
{
  return m_layer;
}

int TicTacTree::get_node_score()const
{
  
}

std::size_t TicTacTree::get_child_count()const
{
  
}

MinimaxState TicTacTree::&get_child(std::size_t index)
{

}
