#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
//#include "player.h"
#include "bullet.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class MyApplication {
public:
    MyApplication();

    ~MyApplication();

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawing_function(sf::RenderWindow &window, sf::RectangleShape player);
    void update_all_bullets(float dt);

    void createBullet(float x_, float y_, float angle_, int damage_);

    void setDeltaTime();
    float getDeltaTime();

private:

    int screenWidth = 1280;
    int screenHeight = 720;

    std::vector<Bullet> all_bullets;

    sf::Clock delta_clock;
    sf::Time delta_time;

};

#endif 
