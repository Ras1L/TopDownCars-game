#ifndef COMMAND_QUEUE_HPP
#define COMMAND_QUEUE_HPP

#include "scene_node.hpp"
#include <queue>

class CommandQueue
{
public:
    void    push(const Command&);
    Command pop();
    bool    isEmpty() const;

private:
    std::queue<Command> mQueue;
};

#include "command_queue.inl"

#endif