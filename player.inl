#include "player.hpp"

Player::Player()
{
    mKeyBinding[sf::Keyboard::Up]    = MoveUp;
    mKeyBinding[sf::Keyboard::Down]  = MoveDown;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Left]  = MoveLeft;

    mKeyBinding[sf::Keyboard::Space] = Fire;
    mKeyBinding[sf::Keyboard::M]     = LaunchMissile;

    initializeActions();
}

void Player::initializeActions()
{
    mActionBinding[MoveUp].action =
    [](SceneNode& node, sf::Time deltaTime) -> void
    {
        node.move(0.f, -PlayerSpeed * deltaTime.asSeconds());
        node.setRotation(0.f);
    };

    mActionBinding[MoveDown].action =
    [](SceneNode& node, sf::Time deltaTime) -> void
    {
        node.move(0.f, PlayerSpeed * deltaTime.asSeconds());
    };

    mActionBinding[MoveRight].action =
    [](SceneNode& node, sf::Time deltaTime) -> void
    {
        node.move(PlayerSpeed * deltaTime.asSeconds(), 0.f);
        node.setRotation(10.f);
    };

    mActionBinding[MoveLeft].action =
    [](SceneNode& node, sf::Time deltaTime) -> void
    {
        node.move(-PlayerSpeed * deltaTime.asSeconds(), 0.f);
        node.setRotation(-10.f);
    };

    // mActionBinding[Fire].action = derivedAction<Car>([](SceneNode& node, sf::Time deltaTime){
    //     Car::fire;
    // });
    // mActionBinding[LaunchMissile].action = derivedAction<Car>([](SceneNode& node, sf::Time deltaTime){
    //     Car::launchMissile;
    // });

    // using namespace std::placeholders;
    // mActionBinding[Fire].action          = derivedAction<Car>(std::bind(&Car::fire, _1));
    // mActionBinding[LaunchMissile].action = derivedAction<Car>(std::bind(&Car::launchMissile, _1));


    /// both variants not working // move logic to that class! ///


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
        output.action   = [](SceneNode& node, sf::Time deltaTime) -> void
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
    switch (action)
    {
        case MoveUp:
        case MoveDown:
        case MoveRight:
        case MoveLeft:
        case Fire:
            return true;
        
        case LaunchMissile:
            return false;

        default:
            return false;
    }
}


void Player::assignKey(Player::Action action, sf::Keyboard::Key key)
{
    mKeyBinding[key] = action;
}

sf::Keyboard::Key Player::getAssignKey(Player::Action action) const
{
    std::for_each(mKeyBinding.begin(), mKeyBinding.end(),
    [action](auto& pair)
    {
        if (pair.second == action){
            return pair.first;
        }
    });
    return sf::Keyboard::Unknown;
}