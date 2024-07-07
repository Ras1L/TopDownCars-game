#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include "scene_node.hpp"


class SpriteNode : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture&);
             SpriteNode(const sf::Texture&, const sf::IntRect&);

public:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates&) const override;

private:
    sf::Sprite mSprite;
};


#include "sprite_node.inl"

#endif