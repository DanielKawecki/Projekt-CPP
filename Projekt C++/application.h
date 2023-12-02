#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "hudText.h"
#include "bullet.h"
#include "enemy.h"
#include "body.h"
#include "tile.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class MyApplication {
private:

    int screenWidth = 1280;
    int screenHeight = 720;

    sf::RenderWindow window;
    sf::View view;

    int points = 0;

    std::vector<Bullet> all_bullets;
    std::vector<Enemy> all_enemies;
    std::vector<Body> all_bodies;
    std::vector<HUDText> all_texts;
    std::vector<Tile> all_tiles;
    std::vector<std::string> map_layout;
    std::vector<std::vector<Tile>> a_star_tiles;

    sf::Clock delta_clock;
    sf::Time delta_time;
    sf::Clock fps_clock;
    sf::Clock break_clock;
    sf::Clock spawn_clock;

    sf::Texture ground_texture;
    sf::Texture column_side_texture;
    sf::Texture column_top_texture;

    sf::Texture bullet_texture;
    sf::Texture player_texture;
    sf::Texture leg_texture;
    sf::Texture body_texture;
    std::vector<sf::Texture> leg_frames;
    sf::Font pixel_font;

    std::unordered_map<std::string, sf::Texture> all_textures;

    int fps = 0.f;

    int enemies_cap = 6;
    int enemies_alive = 0;
    int round = 0;
    bool timer_set = false;

    //void loadTexture(const std::string& filename);

public:
    MyApplication();

    ~MyApplication();

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawingFunction(sf::Sprite player, sf::Sprite player_legs);
    
    void updateAllBullets(float dt);
    void createBullet(float x_, float y_, float angle_, int damage_);
    
    void updateAllEnemies(float player_x, float player_y, float dt);
    void createEnemy(float x, float y);
    
    void updateAllBodies();

    void updateFPS();

    void updatePoints();

    void setBreakTimer();

    void spawn();

    void setDeltaTime();
    float getDeltaTime() const;

    sf::Texture& getPlayerSprite();
    sf::Texture& getLegSprite(int index);
    sf::Texture& getGroundSpirte();

    //void loadTexturesFromDirectory(const std::string& directory);

    //sf::Texture& getTexture(const std::string& filename);

    sf::RenderWindow& getWindow();
    sf::View& getView();

    void updateView(float player_x, float player_y);

    void createTile(float x_, float y_, bool is_wall);

    std::vector<Tile>& getTileVector();

    void setupMap();

    bool mapCollision(float player_x, float player_y);

    std::vector<std::vector<Tile>>& getAStarTiles();
    Tile* getTile(int row, int column);

};

#endif 
