#include "world.hpp"

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
        mWorldBounds.height - mWorldView.getSize().y // Y
    )
, mScrollSpeed(40.f)
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
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    std::shared_ptr<Car> leader(new Car(Car::Challenger, mTextureManager));
    mPlayerCar = leader;
    mPlayerCar->setPosition(mSpawnPosition);
    mPlayerCar->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[Road]->attachChild(std::move(leader));

    std::unique_ptr<Car> leftEscort(new Car(Car::Raptor, mTextureManager));
    leftEscort->setPosition(-80.f, 50.f);
    mPlayerCar->attachChild(std::move(leftEscort));

    std::unique_ptr<Car> rightEscort(new Car(Car::Raptor, mTextureManager));
    rightEscort->setPosition(180.f, 50.f);
    mPlayerCar->attachChild(std::move(rightEscort));
}

void World::draw()
{
    mWindow.setView(mWorldView);
    mWindow.draw(mSceneGraph);
}

void World::update(sf::Time deltaTime)
{
    mWorldView.move(0.f, mScrollSpeed * deltaTime.asSeconds());

    sf::Vector2f position = mPlayerCar->getPosition();
    sf::Vector2f velocity = mPlayerCar->getVelocity();

    if (position.x <= mWorldBounds.left + 150 || 
        position.x >= mWorldBounds.left + mWorldBounds.width - 150)
    {
        velocity.x -= velocity.x;
        mPlayerCar->setVelocity(velocity);
    }

    while (!mCommandQueue.isEmpty()){
        mSceneGraph.onCommand(mCommandQueue.pop(), deltaTime);
    }

    mSceneGraph.update(deltaTime);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}