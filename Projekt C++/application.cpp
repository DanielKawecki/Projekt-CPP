#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
//#include <filesystem>
#include "application.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "body.h"
    
MyApplication::MyApplication() : window(sf::VideoMode(screenWidth, screenHeight), "SFML works!") {

    view.setSize(screenWidth, screenHeight);
    view.setCenter(0.f, 0.f);
    window.setView(view);

    if (!ground_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 200, 16, 16))) {}
    

    if (!bullet_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 150, 80, 5))) {}
    if (!player_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 0, 26, 19))) {}
    if (!body_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 50, 70, 50))) {}
    for (int i = 0; i <= (32 * 6); i = i + 32) {
        leg_texture.loadFromFile("spriteSheet.png", sf::IntRect(100, i, 32, 32));
        leg_frames.push_back(leg_texture);
    }
    for (int i = 0; i <= (32 * 6); i = i + 32) {
        leg_texture.loadFromFile("spriteSheet.png", sf::IntRect(132, i, 32, 32));
        leg_frames.push_back(leg_texture);
    }
    if (!pixel_font.loadFromFile("pixelFont.ttf")) {}
    HUDText fps("0 fps", pixel_font, 28, sf::Color::Black, sf::Vector2f(10.f, 10.f));
    all_texts.push_back(fps);

    HUDText points("0PTS", pixel_font, 28, sf::Color::Black, sf::Vector2f(screenWidth / 2, 10.f));
    all_texts.push_back(points);
}

MyApplication::~MyApplication() {}

int MyApplication::getScreenWidth() const {
    return screenWidth;
}

int MyApplication::getScreenHeight() const {
    return screenHeight;
}

void MyApplication::drawingFunction(sf::Sprite player, sf::Sprite player_legs) {
    window.clear(sf::Color(120, 120, 120, 125));
    
    for (size_t i = 0; i < all_tiles.size(); i++) {
        window.draw(all_tiles[i].getSprite());
    }

    for (size_t i = 0; i < all_bodies.size(); i++) {
        window.draw(all_bodies[i].getSprite());
    }

    for (size_t i = 0; i < all_bullets.size(); i++) {
        window.draw(all_bullets[i].getSprite());
    }

    for (size_t i = 0; i < all_enemies.size(); i++) {
        window.draw(all_enemies[i].getSprite());
    }

    window.draw(player_legs);
    window.draw(player);

    view.setCenter(screenWidth / 2, screenHeight / 2);
    window.setView(view);

    for (size_t i = 0; i < all_texts.size(); i++) {
        window.draw(all_texts[i].getText());
    }

    window.display();
}

void MyApplication::updateAllBullets(float dt) {
    for (auto it = all_bullets.begin(); it != all_bullets.end(); ) {
        it->update(dt);

        if (it->getX() > screenWidth - 50 || it->getX() < 50 ||
            it->getY() > screenHeight - 50 || it->getY() < 50) {
            it = all_bullets.erase(it);
        }
        else {
            ++it;
        }
    }
}

void MyApplication::createBullet(float x_, float y_, float angle_, int damage_) {
    Bullet bullet(x_, y_, angle_, damage_, bullet_texture);
    all_bullets.push_back(bullet);
}

void MyApplication::updateAllEnemies(float player_x, float player_y, float dt) {
    for (auto& enemy : all_enemies) {
        enemy.seekPlayer(player_x, player_y);
        enemy.update(all_enemies, dt);
    }
    
    for (auto it = all_bullets.begin(); it != all_bullets.end(); ++it) {
        for (auto jt = all_enemies.begin(); jt != all_enemies.end(); ) {
            if (jt->checkCollision(it->getX(), it->getY())) {

                if (jt->getHealth(20) <= 0) {
                    Body body(jt->getX(), jt->getY(), it->getAngle(), body_texture);
                    updatePoints();
                    all_bodies.push_back(body);
                    enemies_alive -= 1;
                    jt = all_enemies.erase(jt);
                }
                
                if (enemies_alive == 0)
                    timer_set = false;
                
            }
            else {
                ++jt;
            }
        }
    }
}

void MyApplication::createEnemy(float x, float y) {
    Enemy enemy(x, y, player_texture);
    all_enemies.push_back(enemy);
    enemies_alive += 1;
}

void MyApplication::updateAllBodies() {
    for (auto it = all_bodies.begin(); it != all_bodies.end(); )
        if (it->checkExixtTime())
            it = all_bodies.erase(it);
        else
            ++it;
}

void MyApplication::updateFPS() {
    if (fps_clock.getElapsedTime().asSeconds() >= 1.f) {
        fps = static_cast<int>(std::round(1 / getDeltaTime()));
        all_texts[0].setContent(std::to_string(fps) + " fps");
        fps_clock.restart();
    }
}

void MyApplication::updatePoints() {
    points += 100;
    all_texts[1].setContent(std::to_string(points) + "PTS");
}

void MyApplication::setBreakTimer() {
    if (!timer_set) {
        break_clock.restart();
        timer_set = true;
    }    
}

void MyApplication::spawn() {
    if (spawn_clock.getElapsedTime().asSeconds() >= 1.f && enemies_alive < enemies_cap) {
        //all_texts[1].setContent("alive " + std::to_string(enemies_alive));

        switch (rand() % 4) {
        case 0:
            createEnemy((rand() % 100) + screenWidth + 50, (rand() % 720));
        
        case 1:
            createEnemy((rand() % 100) - 50, (rand() % 720));

        case 2:
            createEnemy((rand() % 1280), (rand() % 100) + screenHeight + 50);

        case 3:
            createEnemy((rand() % 1280), (rand() % 100) - 50);

        default:
            break;
        }
        
        spawn_clock.restart();
    }
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

sf::Texture& MyApplication::getGroundSpirte() {
    return ground_texture;
}

//void MyApplication::loadTexturesFromDirectory(const std::string& directory) {}

//void MyApplication::loadTexture(const std::string& filename) {}

//sf::Texture& MyApplication::getTexture(const std::string& filename) {}

sf::RenderWindow& MyApplication::getWindow() {
    return window;
}

sf::View& MyApplication::getView() {
    return view;
}

void MyApplication::updateView(float player_x, float player_y) {
    view.setCenter(player_x, player_y);
    window.setView(view);
}

void MyApplication::createTile(float x_, float y_) {
    Tile tile(x_, y_, ground_texture);
    all_tiles.push_back(tile);
}
