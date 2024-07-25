#ifndef STATES_H
#define STATES_H

#include <SFML/Graphics.hpp>

namespace States
{
    enum ID
    {
        Title,
        Menu,
        Game,
        Pause
    };
}

class TitleState;
class MenuState;
class GameState;
class PauseState;

#endif