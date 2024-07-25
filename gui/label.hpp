#ifndef GUI_LABEL_HPP
#define GUI_LABEL_HPP

#include "component.hpp"
#include "resource_holder.hpp"

namespace GUI
{

class Label final : public Component
{
public:
    Label(const std::string&, const FontHolder&);
    
    void setText(const std::string&) override;

    bool isSelectable() const        override;

    void draw(sf::RenderTarget&, sf::RenderStates&) const;

private:
    sf::Text mText;
};

}

#include "label.inl"

#endif