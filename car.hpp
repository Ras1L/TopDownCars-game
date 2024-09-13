#ifndef CAR_HPP
#define CAR_HPP

#include "entity.hpp"
#include "resource_holder.hpp"
#include "text_node.hpp"
#include "command_queue.hpp"


class Car final : public Entity
{
public:
    enum Type
    {
        Challenger,
        Raptor,
        Viper,

        TypeCount
    };

public:
    using Ptr = std::shared_ptr<Car>;

public:
    explicit Car(Type, const TextureHolder&, const FontHolder&);

    virtual void drawCurrent(sf::RenderTarget&, sf::RenderStates) const override;

    virtual unsigned int getCategory() const override;
                    void setCategory(Category::Type);

    void update(sf::Time, CommandQueue&);
    void updateMovementPattern(sf::Time);

    void fire();
    void launchMissile();

private:
    float getMaxSpeed();

    void initializeHealthDisplay(const FontHolder&);
    void     updateHealthDisplay();

    void initializeProjectileLogic(const TextureHolder&);
    void createBullets(SceneNode&, const TextureHolder&) const;
    
    void createProjectile(
        SceneNode&, unsigned int, // shit
        float, float, 
        const TextureHolder&
    ) const;

    void checkProjectileLaunch(sf::Time, CommandQueue&);

    bool isAllied() const;

private:
    Type       mType;
    sf::Sprite mSprite;

    std::shared_ptr<TextNode> mHealthDisplay;

    float       mTravelledDistance;
    std::size_t mDirectionIndex;

    bool     mIsFiring;
    sf::Time mFireCountdown; // -----  -
    Command  mFireCommand;
    int      mFireRateLevel; // - -- ---
    int      mSpreadLevel;   // - =

    bool    mIsLaunchingMissile;
    Command mMissileCommand;

    unsigned int mCategory;
};


#include "projectile.hpp"


Textures::ID toTextureID(Car::Type);

namespace
{
    const std::vector<CarData> CarTable = initializeCarData();
}


#include "car.inl"

#endif