#include "display.hpp"

template <class State>
Display<State>::Display(sf::VideoMode mode, const std::string& title)
: mWindow(mode, title)
, mState(mWindow)
{
}

template <class State>
void Display<State>::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        mState.processInput();

        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate >= TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            mState.processInput();
            mState.update(TimePerFrame);
        }
        render();
    }
}

template <class State>
void Display<State>::render()
{
    mWindow.clear();
    mState.draw();
    mWindow.display();
}