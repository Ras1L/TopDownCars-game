#ifndef WORLD_HPP
#define WORLD_HPP

#include "resource_holder.hpp"
#include "sprite_node.hpp"
#include "car.hpp"
#include "player.hpp"


struct SpawnPoint
{
    SpawnPoint(Car::Type type, float x, float y)
    : type(type), x(x), y(y)
    {
    }

    Car::Type type;
    float     x;
    float     y;
};


#include <array>

class World : private sf::NonCopyable
{
public:
    explicit World(sf::RenderWindow&);

    void update(sf::Time);
    void draw();
    void processInput();

    CommandQueue& getCommandQueue();

private:
    void loadResources();
    void buildScene();

    void spawnEnemies();
    void addEnemy(Car::Type, float, float);
    void addEnemies();
    void updateEnemies(sf::Time);

    void guideMissiles();

    sf::FloatRect getBattlefieldBounds();

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
    sf::FloatRect                          mWorldBounds;
    float                                  mScrollSpeed;

    SceneNode                              mSceneGraph;
    std::array<SceneNode::Ptr, LayerCount> mSceneLayers;
    std::vector<SpawnPoint>                mEnemySpawnPoints;
    std::vector<Car::Ptr>                  mEnemies;
    std::vector<Car::Ptr>                  mActiveEnemies;
    CommandQueue                           mCommandQueue;

    TextureHolder                          mTextureManager;
    FontHolder                             mFontManager;

    sf::Vector2f                           mSpawnPosition;
    std::shared_ptr<Car>                   mPlayerCar;
    Player                                 mPlayer;
};

#include "world.inl"

#endif