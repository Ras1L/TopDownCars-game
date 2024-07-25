#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "player.hpp"

template <class State>
class Display
{
public:
    Display(sf::VideoMode, const std::string&);

    void run();

private:
    void render();

private:
    sf::RenderWindow mWindow;
    State            mState;
};

#include "display.inl"

#endif