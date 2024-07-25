#include "application.hpp"

Application::Application()
: mWindow(sf::VideoMode(modeWidth, modeHeight), "SFML APP")
, mStateStack(State::Context
(
    mWindow,
    mTextureManager,
    mFontManager,
    mPlayer
))
{
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<MenuState>(States::Menu);
    mStateStack.registerState<GameState>(States::Game);
    mStateStack.registerState<PauseState>(States::Pause);
}


// Examples
void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen())
    {
        processInput();

        timeSinceLastUpdate += clock.restart();
        while (timeSinceLastUpdate >= TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            update(TimePerFrame);
        }
    }
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);
    }
}

void Application::update(sf::Time deltaTime)
{
    mStateStack.update(deltaTime);
}