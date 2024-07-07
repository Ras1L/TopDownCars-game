#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "scene_node.hpp"

class Entity : public SceneNode
{
public:
    void setVelocity(sf::Vector2f);
    void setVelocity(float vx, float vy);

    sf::Vector2f getVelocity() const;

private:
    virtual void updateCurrent(sf::Time);

private:
    sf::Vector2f mVelocity;
};

#include "entity.inl"

#endif