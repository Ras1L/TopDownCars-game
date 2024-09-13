#include "text_node.hpp"

TextNode::TextNode(const FontHolder& fonts, const std::string& text)
: mText(text, fonts.get(Fonts::Label), 20U)
{
}

void TextNode::setString(const std::string& text)
{
    mText.setString(text);
    centerOrigin(mText);
}

void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mText, states);
}