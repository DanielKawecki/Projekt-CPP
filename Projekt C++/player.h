#include <SFML/Graphics.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif


#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player();

    ~Player();

    sf::RectangleShape draw();

    void setup();

    void move(float dt);

    void look(sf::RenderWindow &window);

    void shoot();

private:
    float x = 100;
    float y = 100;
    float speed_x = 0;
    float speed_y = 0;
    float speed_limit = 450;
    float acceleration = 4600;
    float friction = 2800;

    float angle = 0;

    sf::RectangleShape player_shape = sf::RectangleShape(sf::Vector2f(80.f, 80.f));

};

#endif