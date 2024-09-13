#ifndef MENU_HPP
#define MENU_HPP

#include "button.hpp"
// #include "command_queue.hpp"
// #include "resource_holder.hpp"
// #include "sprite_node.hpp"

#include "world.hpp"
#include "display.hpp"

class Menu : private sf::NonCopyable
{
public:
    explicit Menu(sf::RenderWindow&);

    void draw();
    void update(sf::Time);
    void processInput();

private:
    void buildMenu();
    void loadResources();

private:
    void Play();
    void Exit();

private:
    sf::RenderWindow&                      mWindow;
    TextureHolder                          mTextureManager;
    
    SceneNode                                   mMenuScene;
    std::array<Button::Ptr, Button::LabelCount> mButtons;
    int                                         mButtonIndex;
};

#include "menu.inl"

#endif