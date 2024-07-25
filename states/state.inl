#include "state.hpp"

State::Context::Context(
        sf::RenderWindow& window,
        TextureHolder&    textures,
        FontHolder&       fonts,
        Player&           player
)
: window(&window)
, textures(&textures)
, fonts(&fonts)
, player(&player)
{
}

State::Context State::getContext() const
{
    return mContext;
}