#include "projectile.hpp"

Projectile::Projectile(Type type, const TextureHolder& textureManager)
: Entity(1)

, mType(type)
, mSprite(textureManager.get(ProjectileTable[type].texture))
, mTargetDirection(0.f, 0.f)
{
    centerOrigin(mSprite);
}

void Projectile::guideTowards(sf::Vector2f position)
{
    assert(isGuided());
    mTargetDirection = unitVector(position - getWorldPosition());
}

bool Projectile::isGuided() const
{
    return mType == Projectile::Missile;
}


unsigned int Projectile::getCategory() const
{
    return Category::Projectile;
}

sf::FloatRect Projectile::getBoundingRect() const
{
    return mSprite.getLocalBounds();
}


void Projectile::updateCurrent(sf::Time deltaTime)
{
    if (isGuided())
    {
        const float approachRate = 200.f;

        sf::Vector2f newVelocity = unitVector(approachRate * deltaTime.asSeconds() * mTargetDirection + getVelocity());
                     newVelocity *= getMaxSpeed();
        float angle = std::atan2(newVelocity.y, newVelocity.x);

        setRotation(toDegree(angle));
        setVelocity(newVelocity);
    }
}

void Projectile::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

float Projectile::getMaxSpeed() const
{
    return ProjectileTable[mType].speed;
}

int Projectile::getDamage() const
{
    return ProjectileTable[mType].damage;
}