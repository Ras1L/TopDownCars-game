#include "menu.hpp"

Menu::Menu(sf::RenderWindow& window)
: mWindow(window)
, mButtonIndex(-1)
{
    mWindow.setKeyRepeatEnabled(false);

    loadResources();
    buildMenu();
}


void Menu::loadResources()
{
    mTextureManager.load(Textures::Menu, TEXTURE_DIR + "background/dodge.png");
}

void Menu::buildMenu()
{
    for (auto i = 0; i < Button::LabelCount; ++i)
    {
        mButtons[i] = std::move(std::make_shared<Button>());
    }

    auto windowBounds = mWindow.getDefaultView();
    sf::Texture& texture = mTextureManager.get(Textures::Menu);
    sf::IntRect  textureRect(
        0.f,
        0.f,
        windowBounds.getSize().x,
        windowBounds.getSize().y
    );
    SpriteNode::Ptr background = std::make_shared<SpriteNode>(texture, textureRect);
    mMenuScene.attachChild(std::move(background));

    auto windowCenter = windowBounds.getCenter() / std::sqrt(2.f);

    mButtons[Button::Play]->setPosition(windowCenter.x, windowCenter.y);
    mButtons[Button::Play]->setString("Play");

    mButtons[Button::Exit]->setPosition(windowCenter.x, windowCenter.y + 100.f);
    mButtons[Button::Exit]->setString("Exit");

    mMenuScene.attachChild(mButtons[Button::Play]);
    mMenuScene.attachChild(mButtons[Button::Exit]);
}

void Menu::draw()
{
    mWindow.draw(mMenuScene);
}

void Menu::update(sf::Time deltaTime)
{
    mMenuScene.update(deltaTime);
}

void Menu::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (mButtonIndex >= 0 && mButtons[mButtonIndex]->isSelected())
            {
                mButtons[mButtonIndex]->select(false); // previous button
            }

            if (event.key.code == sf::Keyboard::Down)
            {
                mButtonIndex = (mButtonIndex + 1) % Button::LabelCount;
            }
            else if (event.key.code == sf::Keyboard::Up)
            {
                mButtonIndex = (mButtonIndex + Button::LabelCount - 1) % Button::LabelCount;
            }
            else
            {
            }

            mButtons[mButtonIndex]->select(true); // next button
            
            
            if (event.key.code == sf::Keyboard::Enter)
            {
                if (mButtons[Button::Play]->isSelected())
                {
                    Play();
                }
                else
                if (mButtons[Button::Exit]->isSelected())
                {
                    Exit();
                }
            }
            else
            {
            }
        }
        else if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
}


void Menu::Play()
{
    mWindow.close();
    Display<World> game(sf::VideoMode(modeWidth, modeHeight), "SFML PLAY");
    game.run();
}

void Menu::Exit()
{
    mWindow.close();
}