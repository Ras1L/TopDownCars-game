#ifndef STATE_HPP
#define STATE_HPP

#include "states_identifier.h"
#include "../resource_holder.hpp"
#include "../player.hpp"
#include <memory>

class StateStack;

class State
{
public:
    using Ptr = std::shared_ptr<State>;

    struct Context
    {
        Context(
            sf::RenderWindow&,
            TextureHolder&,
            FontHolder&,
            Player&
        );

        template <class T>
        using Ptr = std::shared_ptr<T>;

        Ptr<sf::RenderWindow> window;
        Ptr<TextureHolder>    textures;
        Ptr<FontHolder>       fonts;
        Ptr<Player>           player;
    };

public:
            State();
            State(StateStack&, Context);
    virtual ~State();

    virtual void draw() = 0;
    virtual bool update(sf::Time) = 0;
    virtual bool handleEvent(const sf::Event&) = 0;

protected:
    void requestStackPush(States::ID);
    void requestStackPop();
    void requestStackClear();

    Context getContext() const;

private:
    std::shared_ptr<StateStack> mStack;
    Context                     mContext;
};

#include "state.inl"

#endif