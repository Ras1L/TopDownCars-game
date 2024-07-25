#include "pause_state.hpp"

void PauseState::draw()
{
    sf::RenderWindow& window = *getContext().window; // wtf: magic *
    window.setView(window.getDefaultView());

    sf::RectangleShape backgroundShape;
    backgroundShape.setFillColor(sf::Color(0, 0, 0, 150));
    backgroundShape.setSize(sf::Vector2f(window.getSize()));

    window.draw(backgroundShape);
    window.draw(mPausedText);
    window.draw(mInstructionText);
}

bool PauseState::handleEvent(const sf::Event& event)
{
    if (event.key.code == sf::Keyboard::Escape)
    {
        requestStackPop(); // return to the game
    }
    else if (event.key.code == sf::Keyboard::BackSpace)
    {
        requestStackClear();
        requestStackPush(States::Menu);
    }

    return false;
}