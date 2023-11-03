#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "bullet.h"
#include "enemy.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class MyApplication {
private:

    int screenWidth = 1280;
    int screenHeight = 720;

    std::vector<Bullet> all_bullets;
    std::vector<Enemy> all_enemies;

    sf::Clock delta_clock;
    sf::Time delta_time;

    sf::Texture bullet_texture;
    sf::Texture player_texture;
    sf::Texture leg_texture;
    sf::Texture body_texture;
    std::vector<sf::Texture> leg_frames;

public:
    MyApplication();

    ~MyApplication();

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawing_function(sf::RenderWindow &window, sf::Sprite player, sf::Sprite player_legs);
    
    void update_all_bullets(float dt);
    void createBullet(float x_, float y_, float angle_, int damage_);
    
    void updateAllEnemies();
    void createEnemy();

    void setDeltaTime();
    float getDeltaTime() const;

    sf::Texture& getPlayerSprite();
    sf::Texture& getLegSprite(int index);

};

#endif 
