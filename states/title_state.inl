#include "title_state.hpp"

bool TitleState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed) // press any key to start
    {
        requestStackPop();
        requestStackPush(States::Menu);
    }
    return true;
}

bool TitleState::update(sf::Time deltaTime)
{
    mTextEffectTime += deltaTime;

    if (mTextEffectTime >= sf::seconds(0.5f))
    {
        mShowText = !mShowText;
        mTextEffectTime = sf::Time::Zero;
    }

    return true;
}