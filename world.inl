#include "world.hpp"
#include <math.h>

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mWorldBounds(
        0.f,                    // left X position
        0.f,                    // top  Y position
        mWorldView.getSize().x, // width
        2000.f                  // height
    )
, mSpawnPosition(
        mWorldView.getSize().x / 2.f,                // X
        mWorldBounds.height// - mWorldView.getSize().y // Y
    )
, mScrollSpeed(-100.f)
, mPlayerCar(nullptr)
{
    loadTextures();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}


void World::loadTextures()
{
    mTextureManager.load(Textures::Challenger, TEXTURE_DIR + "challenger.png");
    mTextureManager.load(Textures::Raptor    , TEXTURE_DIR + "raptor.png");
    mTextureManager.load(Textures::Landscape , TEXTURE_DIR + "landscape.png");
}

void World::buildScene()
{
    for (int i = 0; i < LayerCount; ++i){
        SceneNode::Ptr layer(new SceneNode());
        mSceneLayers[i] = layer;

        mSceneGraph.attachChild(std::move(layer));
    }

    sf::Texture& texture = mTextureManager.get(Textures::Landscape);
    sf::IntRect  textureRect(mWorldBounds);
    texture.setRepeated(true);

    std::shared_ptr<SpriteNode> backgroundSprite(new SpriteNode(texture, textureRect));
    backgroundSprite->setPosition
    (
        mWorldBounds.left,
        mWorldBounds.top
    );
    // backgroundSprite->setPosition(mWorldBounds.left + mWorldBounds.width, mWorldBounds.top);
    // backgroundSprite->setRotation(90.f);
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::shared_ptr<Car> leader(new Car(Car::Challenger, mTextureManager));
    mPlayerCar = leader;
    mPlayerCar->setPosition(mSpawnPosition);
    mPlayerCar->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[Road]->attachChild(std::move(leader));

    // Escort cars
    // std::unique_ptr<Car> leftEscort(new Car(Car::Raptor, mTextureManager));
    // leftEscort->setPosition(-80.f, 50.f);
    // mPlayerCar->attachChild(std::move(leftEscort));

    // std::unique_ptr<Car> rightEscort(new Car(Car::Raptor, mTextureManager));
    // rightEscort->setPosition(180.f, 50.f);
    // mPlayerCar->attachChild(std::move(rightEscort));
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time deltaTime)
{
    // View scrolling
    mWorldView.move(0.f, mScrollSpeed * deltaTime.asSeconds());
    mPlayerCar->setVelocity(0.f, 0.f);

    // Receiving commands
    while (!mCommandQueue.isEmpty()){
        mSceneGraph.onCommand(mCommandQueue.pop(), deltaTime);
    }

    // After execute commands
    sf::Vector2f velocity = mPlayerCar->getVelocity();
    if (velocity.x != 0.f 
     && velocity.y != 0.f)
    {
        mPlayerCar->setVelocity(velocity/std::sqrt(2.f));
    }
    mPlayerCar->accelerate(0.f, mScrollSpeed);

    // Regular update step
    mSceneGraph.update(deltaTime);

    // Compute the rectangle of the current view
    sf::FloatRect viewBounds(
        mWorldView.getCenter() - mWorldView.getSize() / 2.f, // position (left, top)     = 0.f, 0.f
        mWorldView.getSize()                                 // size     (width, height) = width, height of mWorldBounds
    );
    const float borderDistance = 50.f;

    // Handle the case where car leaves visible area
    sf::Vector2f position = mPlayerCar->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);                    // |__
    position.x = std::min(position.x, viewBounds.left + viewBounds.width  - borderDistance);//  __|
    position.y = std::max(position.y, viewBounds.top  + borderDistance);                    // |¯¯
    position.y = std::min(position.y, viewBounds.top  + viewBounds.height - borderDistance);// |__
    mPlayerCar->setPosition(position);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}