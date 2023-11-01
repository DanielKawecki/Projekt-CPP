#include <SFML/Graphics.hpp>
#include "bullet.h"
#include "application.h"
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


#ifndef PLAYER_H
#define PLAYER_H


class Player {
private:
    float x = 100;
    float y = 100;
    float speed_x = 0;
    float speed_y = 0;
    float speed_limit = 450;
    float acceleration = 4600;
    float friction = 2800;

    float angle = 0.f;

    float firerate = 500;
    sf::Clock shot_clock;
    sf::Time shot_cooldown = sf::seconds(10.f);

    MyApplication& App;

    sf::RectangleShape player_shape = sf::RectangleShape(sf::Vector2f(80.f, 80.f));

public:
    Player(MyApplication& App_);

    ~Player();

    sf::RectangleShape draw();

    void setup();

    void move(float dt);

    void look(sf::RenderWindow &window);

    void shoot();

};

#endif