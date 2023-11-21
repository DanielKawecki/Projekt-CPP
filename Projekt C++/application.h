#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "hudText.h"
#include "bullet.h"
#include "enemy.h"
#include "body.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class MyApplication {
private:

    int screenWidth = 1280;
    int screenHeight = 720;

    int points = 0;

    std::vector<Bullet> all_bullets;
    std::vector<Enemy> all_enemies;
    std::vector<Body> all_bodies;
    std::vector<HUDText> all_texts;

    sf::Clock delta_clock;
    sf::Time delta_time;
    sf::Clock fps_clock;
    sf::Clock break_clock;
    sf::Clock spawn_clock;

    sf::Texture bullet_texture;
    sf::Texture player_texture;
    sf::Texture leg_texture;
    sf::Texture body_texture;
    std::vector<sf::Texture> leg_frames;
    sf::Font pixel_font;

    int fps = 0.f;

    int enemies_cap = 3;
    int enemies_alive = 0;
    int round = 0;
    bool timer_set = false;

public:
    MyApplication();

    ~MyApplication();

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawingFunction(sf::RenderWindow &window, sf::Sprite player, sf::Sprite player_legs);
    
    void updateAllBullets(float dt);
    void createBullet(float x_, float y_, float angle_, int damage_);
    
    void updateAllEnemies(float player_x, float player_y, float dt);
    void createEnemy(float x, float y);
    
    void updateAllBodies();

    void updateFPS();

    void updatePoints();

    void setBreakTimer();

    void spawn();

    void setDeltaTime();
    float getDeltaTime() const;

    sf::Texture& getPlayerSprite();
    sf::Texture& getLegSprite(int index);

};

#endif 
