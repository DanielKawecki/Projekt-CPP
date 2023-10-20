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
    float acceleration = 1000;
    float friction = 700;

    sf::CircleShape player_shape = sf::CircleShape::CircleShape(50.f);
    //shape.setFillColor(sf::Color::Green);

};

#endif // APPLICATION_H