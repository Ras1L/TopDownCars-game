#include "entity.hpp"

Entity::Entity(int hitpoints)
{
    mHitpoints = hitpoints;
}

void Entity::damage(int hitpoints)
{
    mHitpoints -= hitpoints;
}

void Entity::repair(int hitpoints)
{
    mHitpoints += hitpoints;
}

void Entity::destroy()
{
    mHitpoints = 0;
}

int Entity::getHitpoints() const
{
    return mHitpoints;
}

bool Entity::isDestroyed() const
{
    return mHitpoints == 0;
}


void Entity::setVelocity(sf::Vector2f velocity)
{
    mVelocity = velocity;
}

void Entity::setVelocity(float vx, float vy)
{
    mVelocity.x = vx;
    mVelocity.y = vy;
}

sf::Vector2f Entity::getVelocity() const
{
    return mVelocity;
}


void Entity::accelerate(sf::Vector2f velocity)
{
    this->setVelocity(this->getVelocity() + velocity);
}

void Entity::accelerate(float vx, float vy)
{
    sf::Vector2f velocity(vx, vy);
    this->setVelocity(this->getVelocity() + velocity);
}


void Entity::updateCurrent(sf::Time deltaTime)
{
    move(mVelocity *= deltaTime.asSeconds());
}


unsigned int Entity::getCategory() const
{
    return Category::AnyCar;
}