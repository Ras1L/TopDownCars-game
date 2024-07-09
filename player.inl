#include "player.hpp"

Player::Player()
{
    mKeyBinding[sf::Keyboard::Up]    = MoveUp;
    mKeyBinding[sf::Keyboard::Down]  = MoveDown;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Left]  = MoveLeft;

    mActionBinding[MoveUp].action =
    [](SceneNode& node, sf::Time deltaTime)
    {
        node.move(0.f, -PlayerSpeed * deltaTime.asSeconds());
    };

    mActionBinding[MoveDown].action =
    [](SceneNode& node, sf::Time deltaTime)
    {
        node.move(0.f, PlayerSpeed * deltaTime.asSeconds());
    };

    mActionBinding[MoveRight].action =
    [](SceneNode& node, sf::Time deltaTime)
    {
        node.move(PlayerSpeed * deltaTime.asSeconds(), 0.f);
    };

    mActionBinding[MoveLeft].action =
    [](SceneNode& node, sf::Time deltaTime)
    {
        node.move(-PlayerSpeed * deltaTime.asSeconds(), 0.f);
    };

    std::for_each(mActionBinding.begin(), mActionBinding.end(),
    [](auto& pair) -> void
    {
        pair.second.category = Category::PlayerCar;
    });
}


void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type     == sf::Event::KeyPressed 
     && event.key.code == sf::Keyboard::P)
    {
        Command output;
        output.category = Category::PlayerCar;
        output.action   = [](SceneNode& node, sf::Time deltaTime)
        {
            printf("X pos: %d, ", "Y pos: %d\n",
                   node.getPosition().x, 
                   node.getPosition().y);
        };
        commands.push(output);
    }
}

void Player::handleRealtimeInput(CommandQueue& commands)
{
    std::for_each(mKeyBinding.begin(), mKeyBinding.end(), [&](auto& pair) -> void
    {
        if (sf::Keyboard::isKeyPressed(pair.first) 
             && this->isRealtimeAction(pair.second))
        {
            commands.push(mActionBinding[pair.second]);
        }
    });
}

bool Player::isRealtimeAction(Action action)
{
    return true;
}