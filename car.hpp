#ifndef CAR_HPP
#define CAR_HPP

#include "entity.hpp"
#include "resource_holder.hpp"

class Car : public Entity
{
public:
    enum Type
    {
        Challenger,
        Raptor
    };

public:
    explicit Car(Type, const TextureHolder&);

    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates&) const override;

    virtual unsigned int getCategory() const override;

private:
    Type mType;
    sf::Sprite mSprite;
};


Textures::ID toTextureID(Car::Type);


#include "car.inl"

#endif