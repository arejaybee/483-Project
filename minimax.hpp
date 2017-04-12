#ifndef MINIMAX_HPP
#define MINIMAX_HPP


class MinimaxState
{
public:
    class const_iterator;

    bool get_node_score() const;

    const_iterator begin() const;
    const_iterator end() const;
};


class MinimaxState::const_iterator
{
public:
    const_iterator &operator++();
    const MinimaxState &operator*();
};


#endif
