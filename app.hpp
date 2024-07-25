#ifndef APP_HPP
#define APP_HPP

#include "menu.hpp"

class Application
{
public:
    Application();

    void run();
    
private:
    sf::VideoMode    mVideoMode;
    std::string      mTitle;

    Display<Menu>    mMenu;
};

#include "app.inl"

#endif