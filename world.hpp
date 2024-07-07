#ifndef WORLD_HPP
#define WORLD_HPP

#include "resource_holder.hpp"
#include "sprite_node.hpp"
#include "car.hpp"
#include "command_queue.hpp"

#include <array>

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow&);

    void update(sf::Time);
    void draw();

    CommandQueue& getCommandQueue();

private:
    void loadTextures();
    void buildScene();

private:
    enum Layer
    {
        Background,
        Road,
        LayerCount
    };

private:
    sf::RenderWindow&                      mWindow;
    sf::View                               mWorldView;
    TextureHolder                          mTextureManager;
    SceneNode                              mSceneGraph;
    std::array<SceneNode::Ptr, LayerCount> mSceneLayers;
    CommandQueue                           mCommandQueue;

    sf::FloatRect                          mWorldBounds;
    sf::Vector2f                           mSpawnPosition;
    float                                  mScrollSpeed;
    std::shared_ptr<Car>                   mPlayerCar;
};


#include "world.inl"

#endif