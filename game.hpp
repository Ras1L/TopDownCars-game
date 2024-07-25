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
    void processInput();
    void render();

private:
    sf::RenderWindow mWindow;
    World            mWorld;
    Player           mPlayer;
    // TextureHolder    textureManager;
};

#include "game.inl"

#endif