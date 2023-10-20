#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player();

    ~Player();

    sf::CircleShape draw();

    void move(float dt);

private:
    float x = 100;
    float y = 100;
    float speed_x = 0;
    float speed_y = 0;
    float speed_limit = 450;
    float acceleration = 4600;
    float friction = 2800;

    sf::CircleShape player_shape = sf::CircleShape::CircleShape(50.f);

};

#endif