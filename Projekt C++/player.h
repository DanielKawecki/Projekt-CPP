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
    float x;
    float y;
    float initial_x = 200;
    float initial_y = 200;
    float speed_x = 0;
    float speed_y = 0;
    float speed_limit = 450;
    float acceleration = 4600;
    float friction = 2800;

    sf::Clock damage_clock;
    sf::Time damage_cooldown = sf::seconds(0.1);
    int health = 100;

    float angle = 0.f;

    float firerate = 600;
    sf::Clock shot_clock;
    sf::Time shot_cooldown = sf::seconds(10.f);

    int ammo = 88;
    int ammo_size = 88;
    int mag = 28;
    int mag_size = 28;
    bool reloading = false;
    sf::Clock reload_clock;
    float reload_time = 1.8;
    sf::RectangleShape reload_rect;

    sf::Clock animation_clock;
    int animation_speed = 65;
    int frame_count = 0;
    bool is_moving = false;

    MyApplication& App;

    sf::RectangleShape player_shape = sf::RectangleShape(sf::Vector2f(80.f, 80.f));
    sf::Sprite player_sprite;
    sf::Sprite legs_sprite;

    sf::FloatRect hitbox;

public:
    Player(MyApplication& App_);

    ~Player();

    sf::Sprite draw();
    sf::Sprite getLegsSprite();

    void move(float dt, std::vector<Tile>& all_tiles, std::vector<Enemy>& all_enemies);

    void look(sf::RenderWindow& window, sf::View& view);

    void shoot();

    float getX() const;
    float getY() const;

    void checkEnemies();

    int getHealth() const;

    void setHealth(int health_);

    void resetPos();

    void reload();

    std::vector<int> getAmmo();

    sf::RectangleShape getReloadRect();

    void resetAmmo();

    sf::FloatRect getRect();

    void addHealth(int amount);
    void addAmmo(int amount);

};

#endif