#ifndef SPRITE_NODE_HPP
#define SPRITE_NODE_HPP

#include "scene_node.hpp"


class SpriteNode final : public SceneNode
{
public:
    explicit SpriteNode(const sf::Texture&);
             SpriteNode(const sf::Texture&, const sf::IntRect&);

    virtual unsigned int getCategory() const override final;

public:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Sprite mSprite;
};


#include "sprite_node.inl"

#endif