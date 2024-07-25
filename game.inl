#include "game.hpp"

Game::Game() 
: mWindow(sf::VideoMode(modeWidth, modeHeight), "SFML APP")
, mWorld(mWindow)
{
    // Loading necessary resources
    // textureManager.load(Textures::Challenger, "./media/texture/challenger.png");

    // After loading necessary resources
    // mPlayer.setTexture(textureManager.get(Textures::Challenger));
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    while (mWindow.isOpen()){
        
        processInput();

        timeSinceLastUpdate += clock.restart();

        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;
            processInput();
            mWorld.update(TimePerFrame);
        }
        render();
    }
}

void Game::processInput()
{
    CommandQueue& commands = mWorld.getCommandQueue();

    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event, commands);

        if (event.type == sf::Event::Closed){
            mWindow.close();
        }
    }
    mPlayer.handleRealtimeInput(commands);
}

void Game::render()
{
    mWindow.clear();
    mWorld.draw();

    // mWindow.setView(mWindow.getDefaultView());
    // mWindow.draw(mPlayer);
    mWindow.display();
}