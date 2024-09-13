#ifndef DATA_TABLES_HPP
#define DATA_TABLES_HPP

#include "global.h"

//////////////////////////////////////////////////////

struct Direction
{
    Direction(float angle, float distance)
    : angle(angle)
    , distance(distance)
    {
    }
    
    float angle;
    float distance;
};

struct CarData
{
    int                    hitpoints;
    float                  speed;
    Textures::ID           texture;
    std::vector<Direction> directions;
};

std::vector<CarData>        initializeCarData();

//////////////////////////////////////////////////////

struct ProjectileData
{
    float        speed;
    int          damage;
    Textures::ID texture;
};

std::vector<ProjectileData> initializeProjectileData();

//////////////////////////////////////////////////////

#include "data_tables.inl"

#endif