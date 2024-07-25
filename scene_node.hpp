#ifndef SCENE_NODE_HPP
#define SCENE_NODE_HPP

class Command;

#include "global.h"
#include <memory>
#include <assert.h>

class SceneNode : public  sf::Transformable, public sf::Drawable,
                  private sf::NonCopyable
{
public:
    using Ptr  = std::shared_ptr<SceneNode>;

public:
    SceneNode() = default;

    void attachChild(Ptr);
    Ptr  detachChild(const SceneNode&);

    sf::Transform getWorldTransform();
    sf::Vector2f  getWorldPosition();

    virtual unsigned int getCategory() const;
    void                 onCommand(const Command&, sf::Time);

    void         update(sf::Time);
private:
    virtual void updateCurrent(sf::Time);
    void         updateChildren(sf::Time);

private:
    virtual void draw(sf::RenderTarget&, sf::RenderStates) const override;

    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates&) const;
    void         drawChildren(sf::RenderTarget&, sf::RenderStates&) const;

private:
    std::vector<Ptr> mChildren;
    Ptr mParent;
};


#include "category.h"
#include <functional>

struct Command
{
    Command() : category(Category::None)
    {
    }

    std::function<void(SceneNode&, sf::Time)> action;
    unsigned int                              category;
};


#include "scene_node.inl"

#endif