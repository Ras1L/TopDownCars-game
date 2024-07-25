#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "command_queue.hpp"

class Player
{
public:
    enum Action
    {
        MoveUp,
        MoveDown,
        MoveRight,
        MoveLeft,

        ActionCount
    };

    Player();

    void                 assignKey(Action, sf::Keyboard::Key);
    sf::Keyboard::Key getAssignKey(Action) const;

public:
    void handleEvent(const sf::Event&, CommandQueue&);
    void handleRealtimeInput(CommandQueue&);

private:
    static bool isRealtimeAction(Action);

private:
    std::unordered_map<sf::Keyboard::Key, Action> mKeyBinding;
    std::unordered_map<Action, Command>           mActionBinding;
};

template <class GameObject, class Function>
std::function<void(SceneNode&, sf::Time)>
derivedAction(Function func)
{
    return
    [=] (SceneNode& node, sf::Time deltaTime) -> void
    {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);

        func(static_cast<GameObject&>(node), deltaTime);
    };
}

struct CarMover
{
    CarMover(float vx, float vy) : velocity(vx, vy)
    {
    }

    void operator()(Car& car, sf::Time deltaTime)
    {
        car.accelerate(velocity); 
    }

    sf::Vector2f velocity;
};

#include "player.inl"

#endif