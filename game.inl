#include "game.hpp"

Game::Game() 
: mWindow(sf::VideoMode(modeWidth, modeHeight), "SFML APP")
, mWorld(mWindow)
//, mPlayer()
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

void Game::processEvents()
{
    sf::Event event;
    while (mWindow.pollEvent(event)){
        switch (event.type)
        {    
            // case sf::Event::KeyPressed:
            //     handlePlayerInput(event.key.code, true);
            //     break;

            // case sf::Event::KeyReleased:
            //     handlePlayerInput(event.key.code, false);
            //     break;

            case sf::Event::Closed:
                mWindow.close();
                break;
        }
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

void Game::update(sf::Time elapsedTime)
{
    sf::Vector2f movement(0.f, 0.f);
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        movement.y -= PlayerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        movement.y += PlayerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        movement.x += PlayerSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        movement.x -= PlayerSpeed;
    }
    // mPlayer.move(movement * elapsedTime.asSeconds());
}

// void Game::update(sf::Time deltaTime)
// {
//     sf::Vector2f movement(0.f, 0.f);

//     if (mIsMovingUp){
//         movement.y -= PlayerSpeed;
//     }
//     if (mIsMovingDown){
//         movement.y += PlayerSpeed;
//     }
//     if (mIsMovingRight){
//         movement.x += PlayerSpeed;
//     }
//     if (mIsMovingLeft){
//         movement.x -= PlayerSpeed;
//     }

//     mPlayer.move(movement * deltaTime.asSeconds());
// }

void Game::render()
{
    mWindow.clear();
    mWorld.draw();

    mWindow.setView(mWindow.getDefaultView());
    // mWindow.draw(mPlayer);
    mWindow.display();
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
    switch (key)
    {
        case sf::Keyboard::W:
            mIsMovingUp = isPressed;
            break;

        case sf::Keyboard::S:
            mIsMovingDown = isPressed;
            break;

        case sf::Keyboard::D:
            mIsMovingRight = isPressed;
            break;

        case sf::Keyboard::A:
            mIsMovingLeft = isPressed;
            break;
    }
}