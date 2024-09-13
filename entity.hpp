#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "scene_node.hpp"

class Entity : public SceneNode
{
public:
    explicit Entity(int);

    void damage(int);
    void repair(int);
    void destroy();

    int  getHitpoints() const;
    bool isDestroyed()  const;

public:
    Entity() = default;

    void setVelocity(sf::Vector2f);
    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity() const;

    void accelerate(sf::Vector2f);
    void accelerate(float, float);

    virtual unsigned int getCategory() const override;

private:
    virtual void updateCurrent(sf::Time);

private:
    int          mHitpoints;
    sf::Vector2f mVelocity;
};

#include "entity.inl"

#endif