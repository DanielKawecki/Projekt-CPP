#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "application.h"
#include "player.h"
    
MyApplication::MyApplication() {}

MyApplication::~MyApplication() {}

int MyApplication::getScreenWidth() const {
    return screenWidth;
}

int MyApplication::getScreenHeight() const {
    return screenHeight;
}

void MyApplication::drawing_function(sf::RenderWindow &window) {
    window.clear();
    //window.draw(all_circles[0]);
    window.draw(player.draw());
    window.display();
}

void MyApplication::add_to_vecor(sf::CircleShape shape) {
    all_circles.push_back(shape);
}