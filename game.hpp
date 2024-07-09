#ifndef GAME_HPP
#define GAME_HPP

#include "world.hpp"
#include "player.hpp"

// Main class of the game
class Game
{
public:
    Game();

    void run();

private:
    void processEvents();
    void processInput();
    void handlePlayerInput(sf::Keyboard::Key, bool); 

    void update(sf::Time);

    void render();

private:
    sf::RenderWindow mWindow;
    World            mWorld;
    Player           mPlayer;
    TextureHolder    textureManager;

    // Flag of the movement
    bool                    mIsMovingUp    = false, 
    mIsMovingLeft  = false, mIsMovingDown  = false, mIsMovingRight = false;
};

#include "game.inl"

#endif