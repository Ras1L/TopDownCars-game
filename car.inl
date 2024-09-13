#include "car.hpp"

Car::Car(Type type, const TextureHolder& textureManager, const FontHolder& fontManager)
: mType(type)
, mSprite(textureManager.get(toTextureID(type)))

, Entity(CarTable[type].hitpoints)

, mTravelledDistance(0.f)
, mDirectionIndex(0)

, mIsFiring(false)
, mIsLaunchingMissile(false)

, mSpreadLevel(1)

, mCategory(Category::PlayerCar)
{
    centerOrigin(mSprite);

    initializeHealthDisplay(fontManager);

    initializeProjectileLogic(textureManager);
}

void Car::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

void Car::update(sf::Time deltaTime, CommandQueue& commands)
{
    updateHealthDisplay();
    checkProjectileLaunch(deltaTime, commands);
}

void Car::updateMovementPattern(sf::Time deltaTime)
{
    const std::vector<Direction>& directions = CarTable[mType].directions;

    if (!directions.empty())
    {
        float distanceToTravel = directions[mDirectionIndex].distance;
        if (mTravelledDistance > distanceToTravel)
        {
            mDirectionIndex = (mDirectionIndex + 1) % directions.size();
            mTravelledDistance = 0.f;
        }
    }

    float radians = toRadian(directions[mDirectionIndex].angle);
    float vx = getMaxSpeed() * std::sin(radians);
    float vy = getMaxSpeed() * std::cos(radians);
    setVelocity(vx, vy);

    mTravelledDistance += getMaxSpeed() * deltaTime.asSeconds();
}


void Car::checkProjectileLaunch(sf::Time deltaTime, CommandQueue& commands)
{
    if (!isAllied())
    {
        fire();
    }
    else 
    {
        if (mIsFiring && mFireCountdown <= sf::Time::Zero)
        {
            commands.push(mFireCommand);
            mFireCountdown += sf::seconds(1.f / (mFireRateLevel + 1));
            mIsFiring = false;
        }
        else if (mFireCountdown > sf::Time::Zero)
        {
            mFireCountdown -= deltaTime;
        }

        if (mIsLaunchingMissile)
        {
            commands.push(mMissileCommand);
            mIsLaunchingMissile = false;
        }
    }
}


void Car::fire()
{
    mIsFiring = true;
}

void Car::launchMissile()
{
    mIsLaunchingMissile = true;
}


unsigned int Car::getCategory() const
{
    return mCategory;
}

void Car::setCategory(Category::Type category)
{
    mCategory = category;
}


float Car::getMaxSpeed()
{
    return CarTable[mType].speed;
}


void Car::initializeHealthDisplay(const FontHolder& fontManager)
{
    mHealthDisplay = std::make_shared<TextNode>(fontManager, "");
    this->attachChild(mHealthDisplay);
}

void Car::updateHealthDisplay()
{
    mHealthDisplay->setString(std::to_string(getHitpoints()) + " HP"); // update health
    mHealthDisplay->setPosition(0.f, 130.f);                          // relative position
    mHealthDisplay->setRotation(-getRotation());                     // text independent of the car's orientation
}


void Car::initializeProjectileLogic(const TextureHolder& textureManager)
{
    mFireCommand.category = Category::PlayerCar; // Category::SceneAirLayer in book
    mFireCommand.action =
    [&textureManager, this](SceneNode& node, sf::Time deltaTime) -> void
    {
        createBullets(node, textureManager);
    };

    mMissileCommand.category = Category::PlayerCar; // Category::SceneAirLayer in book
    mMissileCommand.action =
    [&textureManager, this](SceneNode& node, sf::Time deltaTime) -> void
    {
        createProjectile(node, Projectile::Missile, 0.f, 5.f, textureManager);
    };
}

void Car::createProjectile(SceneNode& node, unsigned int type,
    float xOffset, float yOffset, 
    const TextureHolder& textureManager) const
{
    auto projectile = std::make_shared<Projectile>
    (
        static_cast<Projectile::Type>(type),
        textureManager
    );
    sf::Vector2f offset
    (
        xOffset * mSprite.getGlobalBounds().width,
        yOffset * mSprite.getGlobalBounds().height
    );
    sf::Vector2f velocity(0, projectile->getMaxSpeed());
    float        sign = isAllied() ? -1.f : 1.f;

    projectile->setPosition(getWorldPosition() + offset * sign);
    projectile->setVelocity(velocity * sign);
    node.attachChild(std::move(projectile));
}

void Car::createBullets(SceneNode& node, const TextureHolder& textureManager) const
{
    unsigned int type = isAllied() ? Projectile::AlliedBullet : Projectile::EnemyBullet;

    auto createBulletProjectile =
    [this, &node, type, &textureManager](float x, float y) -> void
    {
        this->createProjectile(node, type, x, y, textureManager);
    };
    switch (mSpreadLevel)
    {
        case 1:
            createBulletProjectile(0.0f, 0.5f);
            break;
        
        case 2:
            createBulletProjectile(-0.33f, 0.33f);
            createBulletProjectile(0.33f, 0.33f);
            break;

        case 3:
            createBulletProjectile(-0.5f, 0.33f);
            createBulletProjectile(0.0f, 0.5f);
            createBulletProjectile(0.5f, 0.33f);
            break;
        
        default:
            break;
    }
}


bool Car::isAllied() const
{
    return getCategory() != Category::EnemyCar;
}


Textures::ID toTextureID(Car::Type type)
{
    switch (type)
    {
        case Car::Challenger:
            return Textures::Challenger;
            break;

        case Car::Raptor:
            return Textures::Raptor;
            break;

        case Car::Viper:
            return Textures::Viper;
            break;
    }
}