#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "application.h"
#include "player.h"
#include "bullet.h"
    
MyApplication::MyApplication() {}

MyApplication::~MyApplication() {}

int MyApplication::getScreenWidth() const {
    return screenWidth;
}

int MyApplication::getScreenHeight() const {
    return screenHeight;
}

void MyApplication::drawing_function(sf::RenderWindow &window, sf::RectangleShape player) {
    window.clear();
    window.draw(player);

    for (size_t i = 0; i < all_bullets.size(); i++) {
        window.draw(all_bullets[i].draw());
    }

    window.display();
}

void MyApplication::add_to_vecor(Bullet bullet) {
    all_bullets.push_back(bullet);
}

sf::Time MyApplication::getDeltaTime() {
    return delta_clock.restart();
}