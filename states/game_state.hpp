#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../world.hpp"
#include "../player.hpp"
#include "state.hpp"

class GameState final : public State
{
public:
    GameState(
        StateStack&,
        Context
    );

    virtual void draw()                        override;
    virtual bool update(sf::Time)              override;
    virtual bool handleEvent(const sf::Event&) override;

private:
    World   mWorld;
    Player& mPlayer;
};

#include "game_state.inl"

#endif