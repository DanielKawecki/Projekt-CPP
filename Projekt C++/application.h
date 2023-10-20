#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "player.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class MyApplication {
public:
    MyApplication();

    ~MyApplication();

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawing_function(sf::RenderWindow &window, sf::CircleShape player);
    void add_to_vecor(sf::CircleShape shape);

    sf::Time getDeltaTime();

private:

    int screenWidth = 1280;
    int screenHeight = 720;

    std::vector<sf::CircleShape> all_circles;

    sf::Clock delta_clock;

    Player player = Player::Player();

};

#endif 
