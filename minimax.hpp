#ifndef MINIMAX_HPP
#define MINIMAX_HPP


#include <utility>


class MinimaxState
{
    public:
        enum Player {PLAYER_MIN, PLAYER_MAX};

        // deconstructor
        virtual ~MinimaxState();

        // the player at a node
        virtual Player get_player() const = 0;

        // the value of a node
        virtual int get_node_score() const = 0;

        // number of children a node has
        virtual std::size_t get_child_count() const = 0;

        // should return a child node given some index
        virtual MinimaxState &get_child(std::size_t index) = 0;
};


// returns <index of optimal child, score>
std::pair<std::size_t, int> minimax_evaluate(MinimaxState &head);


#endif
