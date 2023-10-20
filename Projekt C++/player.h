#include <SFML/Graphics.hpp>

#ifndef PLAYER_H
#define PLAYER_H


class Player {
public:
    Player();

    ~Player();

    sf::CircleShape draw();

private:
    int x = 100;
    int y = 100;

    sf::CircleShape player_shape = sf::CircleShape::CircleShape(100.f);
    //shape.setFillColor(sf::Color::Green);

};

#endif // APPLICATION_H