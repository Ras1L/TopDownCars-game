#include "sprite_node.hpp"

SpriteNode::SpriteNode(const sf::Texture& texture)
{
    mSprite.setTexture(texture);
}

SpriteNode::SpriteNode(const sf::Texture& texture,
                       const sf::IntRect& rectangle)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(rectangle);
}


unsigned int SpriteNode::getCategory() const
{
    return Category::Scene;
}


void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates& states) const
{
    target.draw(mSprite, states);
}