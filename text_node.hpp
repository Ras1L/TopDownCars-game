#ifndef TEXT_NODE_HPP
#define TEXT_NODE_HPP

#include "scene_node.hpp"
#include "resource_holder.hpp"

class TextNode final : public SceneNode
{
public:
    explicit TextNode(const FontHolder&, const std::string&);

    void setString(const std::string&);

private:
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::Text mText;
};

#include "text_node.inl"

#endif