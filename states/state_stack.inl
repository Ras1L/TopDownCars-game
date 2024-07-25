#include "state_stack.hpp"


void StateStack::handleEvent(const sf::Event& event)
{
    std::for_each(mStack.rbegin(), mStack.rend(), //  from the highest state to the lowest
    [&event](auto& state) -> void
    {
        if (!state->handleEvent(event)){
            return;
        }
    });

    applyPendingChanges();
}


template <class T>
void StateStack::registerState(States::ID stateID)
{
    mFactories[stateID] = 
    [this](void) -> State::Ptr
    {
        return State::Ptr(new T(*this, this->mContext));
    };
}

void StateStack::applyPendingChanges()
{
    std::for_each(mPendingList.begin(), mPendingList.end(),
    [this](PendingChanges& change) -> void
    {
        switch (change.action)
        {
            case Push:
                mStack.push_back(createState(change.stateID));
                break;

            case Pop:
                mStack.pop_back();
                break;

            case Clear:
                mStack.clear();
                break;
        }
    });

    mPendingList.clear();
}

State::Ptr StateStack::createState(States::ID stateID)
{
    auto found = mFactories.find(stateID);
    assert(found != mFactories.end());

    return found->second(); // found->second is function that returns State::Ptr
}