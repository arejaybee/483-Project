#ifndef MINIMAX_HPP
#define MINIMAX_HPP


#include <cstddef>


class MinimaxState
{
public:
    virtual ~MinimaxState();

    bool is_leaf() const;
    virtual int get_node_score() const = 0;
    virtual std::size_t get_child_count() const = 0;

    virtual MinimaxState &get_child(std::size_t index) = 0;
};


const MinimaxState &minimax_evaluate(MinimaxState &head);


#endif
