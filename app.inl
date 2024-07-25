#include "app.hpp"

Application::Application()
: mVideoMode(modeWidth, modeHeight)
, mTitle("SFML GAME")
, mMenu(mVideoMode, mTitle)
{
}

void Application::run()
{
    mMenu.run();
}