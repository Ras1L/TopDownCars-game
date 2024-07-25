#ifndef GUI_COMPONENT_HPP
#define GUI_COMPONENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>

namespace GUI
{

class Component : public  sf::Drawable,
                  public  sf::Transformable,
                  private sf::NonCopyable
{
public:
    using Ptr = std::shared_ptr<Component>;

public:
             Component();
    virtual ~Component();

    virtual bool isSelectable() const = 0;
            bool isSelect()     const;
    virtual void select();
    virtual void deselect();

    virtual bool isActive() const;
    virtual void activate();
    virtual void deactivate();

    virtual void handleEvent(const sf::Event&) = 0;

    virtual void setText(const std::string&);

private:
    bool mIsSelected;
    bool mIsActive;
};

}

#endif