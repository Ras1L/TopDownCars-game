#include "data_tables.hpp"

std::vector<CarData> initializeCarData()
{
    std::vector<CarData> data(Car::TypeCount);

    auto& Challenger = data[Car::Challenger];
    Challenger.hitpoints = 100;
    Challenger.speed     = 200.f;
    Challenger.texture   = Textures::Challenger;
    Challenger.directions.emplace_back(0.f, 100.f);

    auto& Raptor = data[Car::Raptor];
    Raptor.hitpoints  = 50;
    Raptor.speed      = 150.f;
    Raptor.texture    = Textures::Raptor;
    Raptor.directions.emplace_back(0.f, 100.f);
    // Raptor.directions.emplace_back(45.f, 80.f);
    // Raptor.directions.emplace_back(-45.f, 160.f);
    // Raptor.directions.emplace_back(45.f, 80.f);

    auto& Viper = data[Car::Viper];
    Viper.hitpoints = 40;
    Viper.speed     = 300.f;
    Viper.texture   = Textures::Viper;
    Viper.directions.emplace_back(0.f, 100.f);
    // Viper.directions.emplace_back(45.f, 50.f);
    // Viper.directions.emplace_back(0.f, 50.f);
    // Viper.directions.emplace_back(-45.f, 100.f);
    // Viper.directions.emplace_back(0.f, 50.f);
    // Viper.directions.emplace_back(45.f, 50.f);

    // More cars...

    return data;
}

std::vector<ProjectileData> initializeProjectileData()
{
    std::vector<ProjectileData> data(Projectile::TypeCount);

    auto& AlliedBullet   = data[Projectile::AlliedBullet];
    AlliedBullet.texture = Textures::AlliedBullet;
    AlliedBullet.speed   = 700.f;
    AlliedBullet.damage  = 20.f;

    auto& EnemyBullet = data[Projectile::EnemyBullet];
    EnemyBullet.texture  = Textures::EnemyBullet;
    EnemyBullet.speed   = 600.f;
    EnemyBullet.damage  = 20.f;

    auto& Missile = data[Projectile::Missile];
    Missile.texture = Textures::Missile;
    Missile.speed   = 600.f;
    Missile.damage  = 150.f;

    // More projectiles...

    return data;
}