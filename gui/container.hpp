#ifndef GUI_CONTAINER_HPP
#define GUI_CONTAINER_HPP

#include "component.hpp"

namespace GUI
{

class Container final : public Component
{
public:
    Container();

    void pack(Component::Ptr);

    bool isSelectable() const override;
    bool hasSelection() const;

    void select(std::size_t);
    void selectPrevious();
    void selectNext();

    void handleEvent(const sf::Event&) override;

    // to remove abstraction of the class
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

private:
    std::vector<Component::Ptr> mChildren;
    int                         mSelectedChild;
};

}

#include "container.inl"

#endif