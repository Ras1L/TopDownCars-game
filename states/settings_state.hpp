#ifndef SETTINGS_STATE_HPP
#define SETTINGS_STATE_HPP

#include "state.hpp"
#include "gui/container.hpp"
#include "gui/label.hpp"
#include "gui/button.hpp"

class SettingsState final : public State
{
public:
    SettingsState(
        StateStack&,
        Context
    );

    virtual void draw()                        override;
    virtual bool update(sf::Time)              override;
    virtual bool handleEvent(const sf::Event&) override;

    void updateLabels();

private:
    GUI::Container mGUIContainer;
    sf::Sprite     mBackgroundSprite;

    std::vector<GUI::Button::Ptr> mBindingButtons;
    std::vector<GUI::Label::Ptr>  mBindingLabels;
};

#include "settings_state.inl"

#endif