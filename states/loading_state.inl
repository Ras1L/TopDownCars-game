#include "loading_state.hpp"

LoadingState::LoadingState(const sf::RenderWindow& window)
{
    mLoadingText.setFont(sf::Font());
    mLoadingText.setString("Loading resources...");
    mLoadingText.setPosition(window.getSize().x / 2u, window.getSize().y / 2u + 50);

    mProgressBarBackground.setFillColor(sf::Color::White);
    mProgressBarBackground.setSize(sf::Vector2f(window.getSize().x - 20.f, 10.f));
    mProgressBarBackground.setPosition(10.f, mLoadingText.getPosition().y + 40.f);

    mProgressBar.setFillColor(sf::Color::Red);
    mProgressBar.setSize(sf::Vector2f(200.f, 10.f));
    mProgressBar.setPosition(10.f, mLoadingText.getPosition().y + 40.f);

    setCompletion(0.f);

    mLoadingTask.execute();
}


bool LoadingState::update(sf::Time deltaTime)
{
    if (mLoadingTask.isFinished())
    {
        requestStackPop();
        requestStackPush(States::Game);
    }
    else
    {
        setCompletion(mLoadingTask.getCompletion());
    }
    return true;
}


void LoadingState::setCompletion(float percent)
{
    if (percent > 1.f){
        percent = 1.f; // TODO
    }
    mProgressBar.setSize(sf::Vector2f
    (
        mProgressBarBackground.getSize().x * percent,
        mProgressBar.getSize().y
    ));

}