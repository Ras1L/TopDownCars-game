#include "parallel_task.hpp"

bool ParallelTask::isFinished()
{
    sf::Lock lock(mMutex);
    return mFinished;
}

void ParallelTask::runTask()
{
    bool ended = false;
    while (!ended)
    {
        sf::Lock lock(mMutex);
        if (mElapsedTime.getElapsedTime().asSeconds() >= 10.f){
            ended = true;
        }
    }

    {
        sf::Lock lock(mMutex);
        mFinished = true;
    }
}