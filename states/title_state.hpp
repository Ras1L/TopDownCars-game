#ifndef TITLE_STATE_HPP
#define TITLE_STATE_HPP

#include "state.hpp"

class TitleState final : public State
{
public:
    TitleState(
        StateStack&,
        Context
    );

    virtual void draw()                        override;
    virtual bool update(sf::Time)              override;
    virtual bool handleEvent(const sf::Event&) override;

private:
    sf::Sprite mBackgroundSprite;
    
    sf::Text   mText;           // Text (example: "press any key")
    bool       mShowText;       // flag of showing text for blinking effect
    sf::Time   mTextEffectTime; // time counter that increments with elapsed time
};

#include "title_state.inl"

#endif