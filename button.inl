#include "button.hpp"

Button::Button()
: mRect(sf::Vector2f(200.f, 50.f))
, mIsSelected(false)
{
    mRect.setFillColor(sf::Color::Yellow);
    
    mFont.loadFromFile("media/font/strogiy.otf");
    mLabel.setFont(mFont);
    mLabel.setFillColor(sf::Color::Red);
    mLabel.setCharacterSize(36u);

    auto rectCoord = mRect.getPosition();
    mLabel.setPosition(rectCoord.x + 50.f, rectCoord.y);
}

void Button::drawCurrent(sf::RenderTarget& target, sf::RenderStates& states) const
{
    target.draw(mRect, states);
    target.draw(mLabel, states);
}

unsigned int Button::getCategory() const
{
    return Category::Button;
}

void Button::setText(const std::string& text)
{
    mLabel.setString(text);
}

void Button::updateCurrent(sf::Time deltaTime)
{
    if (mIsSelected)
    {
        mRect.setFillColor(sf::Color::Blue);
        mLabel.setFillColor(sf::Color::White);
    }
    else
    {
        mRect.setFillColor(sf::Color::Yellow);
        mLabel.setFillColor(sf::Color::Red);
    }
}

void Button::select(bool isSelect)
{
    mIsSelected = isSelect;
}

bool Button::isSelected() const
{
    return mIsSelected;
}

void Button::activate(bool isActive)
{
    mIsActivated = isActive;
}

bool Button::isActivated() const
{
    return mIsActivated;
}