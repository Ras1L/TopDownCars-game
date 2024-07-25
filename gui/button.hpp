#ifndef GUI_BUTTON_HPP
#define GUI_BUTTON_HPP

#include "component.hpp"
#include "../resource_holder.hpp"

#include <functional>

namespace GUI
{

class Button final : public Component
{
public:
    Button(const FontHolder&, const TextureHolder&);

    virtual bool isSelectable() const override;
            bool isSelected()   const;

    virtual void select()     override;
    virtual void deselect()   override;

    virtual void activate()   override;
    virtual void deactivate() override;

    virtual void setText(const std::string&) override;

    // void mCallBack();
    void setCallBack(std::function<void()>);

    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;
    virtual void handleEvent(const sf::Event&)                   override;

private:
    sf::Sprite  mSprite;
    sf::Text    mText;

    sf::Texture mNormalTexture;
    sf::Texture mSelectedTexture;
    sf::Texture mPressedTexture;

    bool mIsToggle;

    std::function<void()> mCallBack;
};

}

#include "button.inl"

#endif