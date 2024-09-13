#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include "entity.hpp"
#include "resource_holder.hpp"


class Projectile : public Entity
{
public:
    enum Type
    {
        None,

        AlliedBullet,
        EnemyBullet,
        Missile,

        TypeCount
    };

public:
    Projectile(Type, const TextureHolder&);

    void guideTowards(sf::Vector2f);
    bool isGuided() const;

    virtual unsigned int  getCategory()     const;
    virtual sf::FloatRect getBoundingRect() const;
    float                 getMaxSpeed()     const;
    int                   getDamage()       const;
                    

private:
    virtual void updateCurrent(sf::Time)                                override;
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
    Type         mType;
    sf::Sprite   mSprite;
    sf::Vector2f mTargetDirection;
};


#include "data_tables.hpp"

namespace
{
    const std::vector<ProjectileData> ProjectileTable = initializeProjectileData();
}


#include "projectile.inl"

#endif