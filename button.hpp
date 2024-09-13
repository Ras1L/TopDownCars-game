#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "text_node.hpp"
#include "resource_holder.hpp"

class Button final : public SceneNode
{
public:
    using Ptr = std::shared_ptr<Button>;
public:
    enum Label
    {
        Play,
        Exit,

        LabelCount
    };

public:
    Button();

    void select(bool);
    bool isSelected() const;

    virtual unsigned int getCategory() const override;

    void setString(const std::string&);

private:
    virtual void updateCurrent(sf::Time) override;
    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

private:
    sf::RectangleShape mRect;

    sf::Font           mFont;
    sf::Text           mLabel;

    bool mIsSelected;
};

#include "button.inl"

#endif