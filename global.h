#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

namespace Textures
{
    enum ID
    {
        // Abstract textures
        Landscape,
        Car, 

        // Textures for Car class
        Challenger,
        Raptor,
        Viper,

        // GUI
        Button,

        // Background textures for states
        TitleScreen,
        Menu,

        // Projectile`s textures
        AlliedBullet,
        EnemyBullet,
        Missile
    };
}

namespace Fonts
{
    enum ID 
    {
        Label
    };
}

// Speed of player
float PlayerSpeed = 70.f;

// FPS (Frame per second)
const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

// Width / Height of the screeen
const unsigned int modeWidth  = 840, modeHeight = 1080;

// Path to texture directory
const std::string TEXTURE_DIR = "./media/texture/";

// Path to font directory
const std::string FONT_DIR = "./media/font/";


// Converts degrees to radians
template <class Tp>
requires(std::floating_point<Tp>)
constexpr Tp toRadian(Tp degrees) noexcept
{
    return degrees * 3.141592 / 180;
}

template <class Tp>
requires(std::floating_point<Tp>)
constexpr Tp toDegree(Tp radian) noexcept
{
    return radian / 3.141592 * 180;
}

template <class Object>
concept ObjectRepresentative = requires(Object& object, sf::FloatRect bounds)
{
    bounds = object.getLocalBounds();
    object.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
};

// Sets the origin of the sprite to the center of the sprite
template <ObjectRepresentative Object>
constexpr void centerOrigin(Object& object) noexcept
{
    sf::FloatRect bounds = object.getLocalBounds();
    object.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

constexpr sf::Vector2f unitVector(sf::Vector2f vec2) noexcept
{
    vec2.x /= vec2.x;
    return vec2;
}


#include "math.h"

constexpr float distance(sf::Vector2f lhs, sf::Vector2f rhs)
{
    return std::sqrt((rhs.x-lhs.x)*(rhs.x-lhs.x) + (rhs.y-lhs.y)*(rhs.y-lhs.y));
}

#endif