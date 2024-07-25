#ifndef PAUSE_STATE_HPP
#define PAUSE_STATE_HPP

#include "state.hpp"

class PauseState final : public State
{
public:
    PauseState(
        StateStack&,
        Context
    );

    virtual void draw()                        override;
    virtual bool update(sf::Time)              override;
    virtual bool handleEvent(const sf::Event&) override;

private:
    sf::Text mPausedText;
    sf::Text mInstructionText;
};

#include "pause_state.inl"

#endif