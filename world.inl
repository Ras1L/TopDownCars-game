#include "world.hpp"

World::World(sf::RenderWindow& window)
: mWindow(window)
, mWorldView(window.getDefaultView())
, mWorldBounds(
        0.f,                    // left X position
        0.f,                    // top  Y position
        mWorldView.getSize().x, // width
        20000.f                 // height
    )
, mSpawnPosition(
        mWorldView.getSize().x / 2.f,                // X
        mWorldBounds.height - 400.f// - mWorldView.getSize().y // Y
    )
, mScrollSpeed(-500.f)
, mPlayerCar(nullptr)
{
    loadResources();
    buildScene();

    mWorldView.setCenter(mSpawnPosition);
}


void World::loadResources()
{
    mTextureManager.load(Textures::Challenger, TEXTURE_DIR + "car/challenger.png");
    mTextureManager.load(Textures::Raptor    , TEXTURE_DIR + "car/raptor.png");
    mTextureManager.load(Textures::Viper     , TEXTURE_DIR + "car/viper.png");
    mTextureManager.load(Textures::Landscape , TEXTURE_DIR + "background/landscape.png");

    mTextureManager.load(Textures::AlliedBullet, TEXTURE_DIR + "projectile/allied_bullet.png");
    mTextureManager.load(Textures::EnemyBullet , TEXTURE_DIR + "projectile/enemy_bullet.png");
    mTextureManager.load(Textures::Missile     , TEXTURE_DIR + "projectile/missile.png");

    mFontManager.load(Fonts::Label, FONT_DIR + "strogiy.otf");
}

void World::buildScene()
{
    // Layers initialization
    for (int i = 0; i < LayerCount; ++i){
        auto layer = std::make_shared<SceneNode>();
        mSceneLayers[i] = layer;

        mSceneGraph.attachChild(std::move(layer));
    }

    // Background
    sf::Texture& texture = mTextureManager.get(Textures::Landscape);
    sf::IntRect  textureRect(mWorldBounds);
    texture.setRepeated(true);

    auto backgroundSprite = std::make_shared<SpriteNode>(texture, textureRect);
    backgroundSprite->setPosition
    (
        mWorldBounds.left,
        mWorldBounds.top
    );
    mSceneLayers[Background]->attachChild(std::move(backgroundSprite));

    // Player Car
    auto leader = std::make_shared<Car>(Car::Challenger, mTextureManager, mFontManager);
    mPlayerCar = leader;
    mPlayerCar->setPosition(mSpawnPosition);
    mPlayerCar->setVelocity(40.f, mScrollSpeed);
    mSceneLayers[Road]->attachChild(std::move(leader));

    // Enemies cars
    addEnemies();

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
    mPlayerCar->update(deltaTime, mCommandQueue);

    // Spawn enemies
    spawnEnemies();

    // Regular update step
    mSceneGraph.update(deltaTime);
    updateEnemies(deltaTime);

    // Compute the rectangle of the current view
    sf::FloatRect viewBounds(
        mWorldView.getCenter() - mWorldView.getSize() / 2.f, // position (left, top)     = 0.f, 0.f
        mWorldView.getSize()                                 // size     (width, height) = width, height of mWorldBounds
    );

    // Handle the case where car leaves visible area
    const float borderDistance = 100.f;
    sf::Vector2f position = mPlayerCar->getPosition();
    position.x = std::max(position.x, viewBounds.left + borderDistance);                            // |__
    position.x = std::min(position.x, viewBounds.left + viewBounds.width  - borderDistance);        //  __|
    position.y = std::max(position.y, viewBounds.top  + borderDistance + 200.f);                    // |¯¯
    position.y = std::min(position.y, viewBounds.top  + viewBounds.height - borderDistance - 200.f);// |__
    mPlayerCar->setPosition(position);
}

void World::spawnEnemies()
{
    while (!mEnemySpawnPoints.empty()
         && mEnemySpawnPoints.back().y > getBattlefieldBounds().top)
    {
        SpawnPoint spawn = mEnemySpawnPoints.back();

        auto enemy = std::make_shared<Car>(spawn.type, mTextureManager, mFontManager);
        enemy->setPosition(spawn.x, spawn.y);
        enemy->setRotation(180.f);
        enemy->setCategory(Category::EnemyCar);

        mSceneLayers[Road]->attachChild(enemy);
        mEnemies.push_back(std::move(enemy));

        mEnemySpawnPoints.pop_back();
    }
}

void World::addEnemy(Car::Type type, float x, float y)
{
    mEnemySpawnPoints.push_back(SpawnPoint(type, mWorldView.getCenter().x + x, mWorldBounds.height - y));
}

void World::addEnemies()
{
    addEnemy(Car::Raptor,      55.f, 4900.f);
    addEnemy(Car::Viper,      -75.f, 3700.f);
    addEnemy(Car::Challenger, -75.f, 2600.f);
    addEnemy(Car::Raptor,      55.f, 1900.f);

    std::sort(mEnemySpawnPoints.begin(), mEnemySpawnPoints.end(),
    [](SpawnPoint lhs, SpawnPoint rhs)
    {
        return lhs.y < rhs.y;
    });
}

void World::updateEnemies(sf::Time deltaTime)
{
    std::for_each(mEnemies.begin(), mEnemies.end(),
    [deltaTime, this](Car::Ptr enemy)
    {
        enemy->update(deltaTime, getCommandQueue());
        enemy->updateMovementPattern(deltaTime);
    });
}


void World::guideMissiles()
{
    Command enemyCollector;
    enemyCollector.category = Category::EnemyCar;
    enemyCollector.action   =
    [this](SceneNode& node, sf::Time)
    {
        Car& enemy = static_cast<Car&>(node);

        if (enemy.isDestroyed())
        {
            mActiveEnemies.push_back(Car::Ptr(&enemy));
        }
    };

    Command missileGuider;
    missileGuider.category = Category::Projectile;
    missileGuider.action = derivedAction<Projectile>(
    [this] (SceneNode& node, sf::Time)
    {
        Projectile& missile = static_cast<Projectile&>(node);

        // Ignore unguided bullets
        if (!missile.isGuided())
        {
            return;
        }
        float minDistance = std::numeric_limits<float>::max();
        auto closestEnemy = Car::Ptr(nullptr);

        std::for_each(mActiveEnemies.begin(), mActiveEnemies.end(),
        [&](Car::Ptr enemy)
        {
            float enemyDistance = distance(missile.getPosition(), enemy->getPosition());
            if (enemyDistance < minDistance)
            {
                closestEnemy = enemy;
                minDistance = enemyDistance;
            }
        });

        if (closestEnemy)
        {
            missile.guideTowards(closestEnemy->getWorldPosition());
        }
    });

    mCommandQueue.push(enemyCollector);
    mCommandQueue.push(missileGuider);

    mActiveEnemies.clear();
}


void World::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mPlayer.handleEvent(event, mCommandQueue);

        if (event.type == sf::Event::Closed)
        {
            mWindow.close();
        }
    }
    mPlayer.handleRealtimeInput(mCommandQueue);
}

CommandQueue& World::getCommandQueue()
{
    return mCommandQueue;
}

sf::FloatRect World::getBattlefieldBounds()
{
    return sf::FloatRect
    (
        mWorldView.getCenter() - mWorldView.getSize() / 1.6f,
        mWorldView.getSize()
    ); 
}