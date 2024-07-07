#include "car.hpp"

Textures::ID toTextureID(Car::Type type)
{
    switch (type)
    {
        case Car::Challenger:
            return Textures::Challenger;

        case Car::Raptor:
            return Textures::Raptor;
    }
}

Car::Car(Type type, const TextureHolder& textureManager)
: mType(type)
, mSprite(textureManager.get(toTextureID(type)))
{
    sf::FloatRect bounds = mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void Car::drawCurrent(sf::RenderTarget& target, sf::RenderStates& states) const
{
    target.draw(mSprite, states);
}