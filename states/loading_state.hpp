#ifndef LOADING_STATE_HPP
#define LOADING_STATE_HPP

#include "state.hpp"
#include "parallel_task.hpp"

class LoadingState final : public State
{
public:
    LoadingState(const sf::RenderWindow&);

    virtual bool update(sf::Time) override;

private:
    void setCompletion(float);

private:
    sf::Text           mLoadingText;
    sf::RectangleShape mProgressBarBackground;
    sf::RectangleShape mProgressBar;
    ParallelTask       mLoadingTask;
};

#include "loading_state.inl"

#endif