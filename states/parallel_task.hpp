#ifndef PARALLEL_TASK_HPP
#define PARALLEL_TASK_HPP

#include "state.hpp"

class ParallelTask
{
public:
    ParallelTask();

    void  execute();
    bool  isFinished();
    float getCompletion();

private:
    void runTask();

private:
    sf::Thread mThread;
    bool       mFinished;
    sf::Clock  mElapsedTime;
    sf::Mutex  mMutex;
};

#include "parallel_task.inl"

#endif