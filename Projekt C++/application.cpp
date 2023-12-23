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

    if (!ground_texture.loadFromFile("spriteSheet2.png", sf::IntRect(4*32, 32, 32, 32))) {}
    if (!column_side_texture.loadFromFile("spriteSheet2.png", sf::IntRect(4*32, 0, 32, 32))) {}
    if (!column_top_texture.loadFromFile("spriteSheet.png", sf::IntRect(64, 170, 32, 32))) {}

    if (!bullet_texture.loadFromFile("spriteSheet2.png", sf::IntRect(96, 32, 32, 4))) {}
    if (!player_texture.loadFromFile("spriteSheet2.png", sf::IntRect(3*32, 0, 30, 10))) {}
    if (!body_texture.loadFromFile("spriteSheet.png", sf::IntRect(0, 50, 70, 50))) {}
    
    for (int i = 0; i < (32 * 12); i = i + 32) {
        leg_texture.loadFromFile("spriteSheet2.png", sf::IntRect(0, i, 32, 32));
        leg_frames.push_back(leg_texture);
    }

    for (int i = 0; i < (32 * 12); i = i + 32) {
        enemy_texture.loadFromFile("spriteSheet2.png", sf::IntRect(32, i, 32, 32));
        enemy_frames.push_back(enemy_texture);
    }

    if (!pixel_font.loadFromFile("pixelFont.ttf")) {}
    HUDText fps("0 fps", pixel_font, 28, sf::Color::White, sf::Vector2f(10.f, 10.f), false);
    all_texts.push_back(fps);

    HUDText points("0PTS", pixel_font, 28, sf::Color::White, sf::Vector2f(screenWidth - 150.f, 10.f), false);
    all_texts.push_back(points);

    HUDText health("100HP", pixel_font, 28, sf::Color::White, sf::Vector2f(screenWidth - 150.f, 40.f), false);
    all_texts.push_back(health);
}

MyApplication::~MyApplication() {}

int MyApplication::getScreenWidth() const {
    return screenWidth;
}

int MyApplication::getScreenHeight() const {
    return screenHeight;
}

void MyApplication::drawingFunction(sf::Sprite player, sf::Sprite player_legs) {
    window.clear(sf::Color(26, 26, 26, 255));
    
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

    view.setCenter(screenWidth / 2.f, screenHeight / 2.f);
    window.setView(view);

    if (pause) {

        window.draw(pauseOverlay);

        HUDText pause_text("GAME PAUSED", pixel_font, 40, sf::Color::White, sf::Vector2f(screenWidth/2, (screenHeight/2)-40), true);
        window.draw(pause_text.getText());
    }

    if (game_over) {
        window.draw(pauseOverlay);

        HUDText game_over_text("GAME OVER", pixel_font, 40, sf::Color::White, sf::Vector2f(screenWidth / 2, (screenHeight / 2) - 40), true);
        HUDText reset_text("Press SPACE to start again", pixel_font, 30, sf::Color::White, sf::Vector2f(screenWidth / 2, (screenHeight / 2) + 10), true);
        
        window.draw(game_over_text.getText());
        window.draw(reset_text.getText());
    }

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

    player_tile = getTile((int)floor(player_x/64), (int)floor(player_y/64));

    for (auto& enemy : all_enemies) {

        enemy_tile = getTile((int)floor(enemy.getX() / 64), (int)floor(enemy.getY() / 64));
        
        enemy.seekPlayer(enemy_tile, player_tile, getAStarTiles());
        enemy.update(all_enemies, dt);
    }

    for (auto it = all_bullets.begin(); it != all_bullets.end(); ) {
        bool bulletRemoved = false;  
        it->update(dt);

        for (auto jt = all_enemies.begin(); jt != all_enemies.end(); ) {
            if (jt->checkCollision(it->getX(), it->getY())) {
                if (jt->getHealth(20) <= 0) {
                    //Body body(jt->getX(), jt->getY(), it->getAngle(), body_texture);
                    updatePoints();
                    //all_bodies.push_back(body);
                    enemies_alive -= 1;
                    jt = all_enemies.erase(jt);
                }

                it = all_bullets.erase(it);
                bulletRemoved = true;
                break;  
            }
            else {
                ++jt;
            }
        }

        if (!bulletRemoved) {
            for (const auto& tile : all_tiles) {
                if (tile.checkCollision(it->getX(), it->getY()) && tile.isWall()) {
                    it = all_bullets.erase(it);
                    bulletRemoved = true;
                    break;  
                }
            }
        }

        if (!bulletRemoved) {
            ++it;
        }
    }
}


void MyApplication::createEnemy(float x, float y) {
    Enemy enemy(x, y, enemy_frames);
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

        float choice = rand() % all_spawnpoints.size();
        createEnemy(all_spawnpoints[choice].x, all_spawnpoints[choice].y);
        
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

void MyApplication::createTile(float x_, float y_, bool is_wall, bool is_spawn) {
    if (is_wall) {
        Tile tile(x_, y_, column_side_texture, is_wall, is_spawn);
        all_tiles.push_back(tile);
    }

    else {
        Tile tile(x_, y_, ground_texture, false, false);
        all_tiles.push_back(tile);
    }
}

std::vector<Tile>& MyApplication::getTileVector() {
    return all_tiles;
}

void MyApplication::setupMap() {
    map_layout = {
        "####################",
        "#s       #        s#",
        "#        #         #",
        "#   ##       ##    #",
        "#        #         #",
        "#        #         #",
        "#### ######### #####",
        "#        #         #",
        "#        #         #",
        "#   ##       ##    #",
        "#        #         #",
        "#s       #        s#",
        "####################"
    };

    const float tile_size = 64.0f;
    a_star_tiles.resize(map_layout.size(), std::vector<Tile>(map_layout[0].size(), Tile(0.0f, 0.0f, ground_texture, false, false)));


    for (size_t i = 0; i < map_layout.size(); ++i) {
        for (size_t j = 0; j < map_layout[i].size(); ++j) {
            if (map_layout[i][j] == '#') {
                createTile(j * tile_size, i * tile_size, true, false);
                a_star_tiles[i][j] = Tile(j * tile_size, i * tile_size, column_side_texture, true, false);
            }
            else if (map_layout[i][j] == 's') {
                createTile(j * tile_size, i * tile_size, false, true);
                a_star_tiles[i][j] = Tile(j * tile_size, i * tile_size, ground_texture, false, true);
                all_spawnpoints.push_back(sf::Vector2f(j * tile_size, i * tile_size));
            }
            else {
                createTile(j * tile_size, i * tile_size, false, false);
                a_star_tiles[i][j] = Tile(j * tile_size, i * tile_size, ground_texture, false, false);
            }
                
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) 
                    if (di * di + dj * dj == 1)
                    {
                        int ni = static_cast<int>(i) + di;
                        int nj = static_cast<int>(j) + dj;
                        if (ni >= 0 && ni < a_star_tiles.size() && nj >= 0 && nj < a_star_tiles[i].size() && !a_star_tiles[ni][nj].isWall()) {
                            a_star_tiles[i][j].addNeighbor(&a_star_tiles[ni][nj]);
                        }
                    }
            }

        }
    }
}

bool MyApplication::mapCollision(float player_x, float player_y) {
    for (auto& tile : all_tiles) {
        if (tile.isWall() && tile.checkCollision(player_x, player_y))
            return true;
    }

    return false;
}

bool MyApplication::enemyCollision(float player_x, float player_y) {
    for (auto& enemy : all_enemies) {
        if (enemy.checkCollision(player_x, player_y))
            return true;
    }

    return false;
}

std::vector<std::vector<Tile>>& MyApplication::getAStarTiles() {
    return a_star_tiles;
}

Tile* MyApplication::getTile(int row, int column) {
    return &a_star_tiles[column][row];
}

bool MyApplication::isPause() {
    return pause;
}

void MyApplication::setPause() {
    static bool prev_escape = false;
    bool current_escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

    if (current_escape && !prev_escape) {
        pause = !pause;
    }

    prev_escape = current_escape;
}

void MyApplication::setupOverlay() {
    pauseOverlay.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
    pauseOverlay.setFillColor(sf::Color(0, 0, 0, 150));
}

std::vector<Enemy>& MyApplication::getEnemiesVector() {
    return all_enemies;
}

void MyApplication::updateHealth(int health) {
    all_texts[2].setContent(std::to_string(health) + "HP");

    if (health == 0)
        game_over = true;
}

bool MyApplication::isGameOver() {
    return game_over;
}

void MyApplication::reset() {
    points = 0;
    enemies_alive = 0;
    all_texts[1].setContent(std::to_string(0) + "PTS");
    game_over = false;
    
    all_enemies.clear();
    all_bodies.clear();

}

bool MyApplication::checkForReset() {
    static bool prev_space = false;
    bool current_space = sf::Keyboard::isKeyPressed(sf::Keyboard::Space);

    if (current_space && !prev_space) {
        reset();
        return true;
    }

   
    prev_space = current_space;
    return false;
}
