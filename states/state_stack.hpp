#ifndef STATE_STACK_HPP
#define STATE_STACK_HPP

#include "title_state.hpp"
#include "menu_state.hpp"
#include "game_state.hpp"
#include "pause_state.hpp"

#include <unordered_map>
#include <functional>
#include <assert.h>

class StateStack : private sf::NonCopyable
{
public:
    enum Action
    {
        Push,
        Pop,
        Clear
    };

public:
    explicit StateStack(State::Context);

    void draw();
    void update(sf::Time);
    void handleEvent(const sf::Event&);

    template <class T>
    void registerState(States::ID);
    void pushState(States::ID);
    void popState();
    void clearStates();

    bool isEmpty() const;

private:
    State::Ptr createState(States::ID);
    void       applyPendingChanges();

private:
    struct PendingChanges
    {
        Action     action;
        States::ID stateID;
    };

private:
    std::vector<State::Ptr>     mStack;
    std::vector<PendingChanges> mPendingList;
    State::Context              mContext;

    std::unordered_map
    <States::ID, std::function<State::Ptr(void)>>
    mFactories;
};

#include "state_stack.inl"

#endif