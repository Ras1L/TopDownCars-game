#ifndef MENU_STATE_HPP
#define MENU_STATE_HPP

#include "state.hpp"
#include "../gui/container.hpp"
#include "../gui/button.hpp"

class MenuState final : public State
{
public:
    MenuState(
        StateStack&,
        Context
    );

    virtual void draw()                        override;
    virtual bool update(sf::Time)              override;
    virtual bool handleEvent(const sf::Event&) override;

    void updateOptionText();

public:
    enum OptionName
    {
        Play,
        Exit
    };

private:
    std::vector<sf::Text> mOptions;
    std::size_t           mOptionIndex;

    GUI::Container        mGUIContainer;
    sf::Sprite            mBackgroundSprite;
};

#include "menu_state.inl"

#endif