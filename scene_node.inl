#include "scene_node.hpp"

void SceneNode::attachChild(Ptr child)
{
    child->mParent = Ptr(this);
    mChildren.emplace_back(child);
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& child)
{
    auto found = std::find_if(mChildren.begin(), mChildren.end(), [&child](Ptr& node) -> bool // &child - взятие по ссылке
    {
        return node.get() == &child;                                                        // &child - взятие адреса
    });
    assert(found != mChildren.end());

    Ptr result = std::move(*found);
    result->mParent = nullptr;
    mChildren.erase(found);

    return result;
}


sf::Transform SceneNode::getWorldTransform() // const
{
    sf::Transform transform = sf::Transform::Identity;
    for (Ptr node = Ptr(this); node != nullptr; node = node->mParent)
    {
        transform *= node->getTransform();
    }
    return transform;
}

sf::Vector2f SceneNode::getWorldPosition() // const
{
    return getWorldTransform() * sf::Vector2f();
}


unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}

void SceneNode::onCommand(const Command& command, sf::Time deltaTime)
{
    if (command.category & this->getCategory()){
        command.action(*this, deltaTime);
    }

    std::for_each(mChildren.begin(), mChildren.end(), [&](Ptr& node){
        node->onCommand(command, deltaTime);
    });
}


void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();

    drawCurrent(target, states);
    drawChildren(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates& states) const
{
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates& states) const
{
    std::for_each(mChildren.begin(), mChildren.end(), [&target, &states](Ptr node){
        node->draw(target, states);
    });
}


void SceneNode::update(sf::Time deltaTime)
{
    updateCurrent(deltaTime);
    updateChildren(deltaTime);
}

void SceneNode::updateCurrent(sf::Time deltaTime)
{
}

void SceneNode::updateChildren(sf::Time deltaTime)
{
    std::for_each(mChildren.begin(), mChildren.end(), [&deltaTime](Ptr& node){
        node->update(deltaTime);
    });
}