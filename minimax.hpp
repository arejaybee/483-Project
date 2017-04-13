#ifndef MINIMAX_HPP
#define MINIMAX_HPP


#include <cstddef>


class MinimaxState
{
public:
    virtual ~MinimaxState();

    virtual bool is_leaf() const = 0;
    virtual int get_node_score() const = 0;

    virtual std::size_t get_number_of_children() const = 0;

    // will be freed upon destruction
    virtual MinimaxState *get_child(std::size_t index) = 0;
};


#endif
