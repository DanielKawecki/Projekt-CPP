#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "application.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
    
MyApplication::MyApplication() {
    if (!bullet_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 150, 80, 5))) {}
    if (!player_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 0, 26, 19))) {}
    for (int i = 0; i <= (32 * 6); i = i + 32) {
        leg_texture.loadFromFile("spriteSheet.png", sf::IntRect(100, i, 32, 32));
        leg_frames.push_back(leg_texture);
    }
    for (int i = 0; i <= (32 * 6); i = i + 32) {
        leg_texture.loadFromFile("spriteSheet.png", sf::IntRect(132, i, 32, 32));
        leg_frames.push_back(leg_texture);
    }
}

MyApplication::~MyApplication() {}

int MyApplication::getScreenWidth() const {
    return screenWidth;
}

int MyApplication::getScreenHeight() const {
    return screenHeight;
}

void MyApplication::drawing_function(sf::RenderWindow &window, sf::Sprite player, sf::Sprite player_legs) {
    window.clear(sf::Color(120, 120, 120, 125));

    for (size_t i = 0; i < all_bullets.size(); i++) {
        window.draw(all_bullets[i].getSprite());
    }
    
    for (size_t i = 0; i < all_enemies.size(); i++) {
        window.draw(all_enemies[i].getSprite());
    }

    window.draw(player_legs);
    window.draw(player);

    window.display();
}

void MyApplication::update_all_bullets(float dt) {
    for (size_t i = 0; i < all_bullets.size(); i++) {
        all_bullets[i].update(dt);

        if (all_bullets[i].getX() > screenWidth - 50 || all_bullets[i].getX() < 50)
            all_bullets.erase(all_bullets.begin() + i);
        else if (all_bullets[i].getY() > screenHeight - 50 || all_bullets[i].getY() < 50)
            all_bullets.erase(all_bullets.begin() + i);
    }
}

void MyApplication::createBullet(float x_, float y_, float angle_, int damage_) {
    Bullet bullet(x_, y_, angle_, damage_, bullet_texture);
    all_bullets.push_back(bullet);
}

void MyApplication::createEnemy() {
    Enemy enemy(500.f, 250.f, player_texture);
    all_enemies.push_back(enemy);
}

void MyApplication::setDeltaTime() {
    delta_time = delta_clock.restart();
}

float MyApplication::getDeltaTime() const {
    return delta_time.asSeconds();
}

sf::Texture& MyApplication::getPlayerSprite() {
    return player_texture;
}

sf::Texture& MyApplication::getLegSprite(int index) {
    return leg_frames[index];
}