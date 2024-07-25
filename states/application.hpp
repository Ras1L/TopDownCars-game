#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include "state_stack.hpp"

class Application
{
public:
    Application();

    void registerStates();

    void run();

    void processInput();
    void update(sf::Time);

private:
    StateStack       mStateStack;

    sf::RenderWindow mWindow;
    TextureHolder    mTextureManager;
    FontHolder       mFontManager;
    Player           mPlayer;
};

#include "application.inl"

#endif