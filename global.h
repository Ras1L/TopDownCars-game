#ifndef GLOBAL_H
#define GLOBAL_H

#include <SFML/Graphics.hpp>

namespace Textures
{
    enum ID {
        // Abstract textures
        Landscape,
        Car, 
        Missile,

        // Textures for Car class
        Challenger,
        Raptor
    };
}

// Speed of player
float PlayerSpeed = 70.f;

// FPS (Frame per second)
const sf::Time TimePerFrame = sf::seconds(1.f/60.f);

// Width / Height of the screeen
const unsigned int modeWidth  = 640, modeHeight = 1080;

// Path to texture directory
const std::string TEXTURE_DIR = "./media/texture/";

#endif