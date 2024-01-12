#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include <vector>
#include "hudText.h"
#include "bullet.h"
#include "enemy.h"
#include "body.h"
#include "tile.h"
#include "refill.h"

#ifndef APPLICATION_H
#define APPLICATION_H

class MyApplication {
private:

    int screenWidth = 1280;
    int screenHeight = 720;

    sf::RenderWindow window;
    sf::View view;

    int points = 0;
    int highest_score = 0;
    const std::string filePath = "bestScore.txt";

    bool game_started = false;
    bool is_reset = false;
    bool pause = false;
    sf::RectangleShape pauseOverlay;

    bool game_over = false;

    Tile* player_tile = nullptr;
    Tile* enemy_tile = nullptr;

    std::vector<Bullet> all_bullets;
    std::vector<Enemy> all_enemies;
    std::vector<Body> all_bodies;
    std::vector<HUDText> all_texts;
    std::vector<Tile> all_tiles;
    std::vector<std::string> map_layout;
    std::vector<std::vector<Tile>> a_star_tiles;
    std::vector<sf::Vector2f> all_spawnpoints;
    std::vector<Refill> health_refill;
    std::vector<Refill> ammo_refill;
    std::vector<int> refill_points_indexes;

    sf::Clock delta_clock;
    sf::Time delta_time;
    sf::Clock fps_clock;
    sf::Clock break_clock;
    sf::Clock spawn_clock;
    sf::Clock playtime;

    sf::Texture ground_texture;
    sf::Texture column_side_texture;
    sf::Texture column_top_texture;

    sf::Texture bullet_texture;
    sf::Texture player_texture;
    sf::Texture enemy_texture;
    sf::Texture leg_texture;
    sf::Texture body_texture;
    std::vector<sf::Texture> leg_frames;
    std::vector<sf::Texture> enemy_frames;
    sf::Texture health_pack_texture;
    sf::Texture ammo_pack_texture;
    sf::Font pixel_font;

    sf::Image cursor_image;
    sf::Cursor cursor;

    sf::Texture cursor_texture;
    sf::Sprite cursor_sprite;

    std::unordered_map<std::string, sf::Texture> all_textures;

    int fps = 0.f;

    int enemies_cap = 6;
    int enemies_alive = 0;
    int round = 0;
    bool timer_set = false;

    sf::Clock health_cooldown;
    sf::Clock ammo_cooldown;

    //void loadTexture(const std::string& filename);

public:
    MyApplication();

    ~MyApplication();

    int getScreenWidth() const;
    int getScreenHeight() const;

    void drawStartingScreen(sf::Event& event);
    void drawingFunction(sf::Sprite player, sf::Sprite player_legs, sf::RectangleShape reload_rect, sf::Event& event);
    
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

    void createTile(float x_, float y_, bool is_wall, bool is_spawn);

    std::vector<Tile>& getTileVector();

    void setupMap();

    bool mapCollision(float player_x, float player_y);

    bool enemyCollision(sf::FloatRect player_hitbox);

    std::vector<std::vector<Tile>>& getAStarTiles();

    Tile* getTile(int row, int column);

    bool isPause();

    void setPause();

    void setupOverlay();

    std::vector<Enemy>& getEnemiesVector();

    void updateHealth(int health);

    bool isGameOver();

    void reset();

    bool checkForReset();

    void updateAmmo(std::vector<int> ammo_vecotr_);

    bool checkHealthRefill(sf::FloatRect player_hitbox);
    bool checkAmmoRefill(sf::FloatRect player_hitbox);

    void createHealthRefill(float x, float y);
    void createAmmoRefill(float x, float y);

    bool healthRefillCollision(sf::FloatRect player_hitbox);
    bool ammoRefillCollision(sf::FloatRect player_hitbox);

    void setReset(bool is_reset_);

    bool gameStarted();

    void checkBestScore();

    void resetClocks();

};

#endif 
