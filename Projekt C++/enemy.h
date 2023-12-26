#include <SFML/Graphics.hpp>
#include "BFS.h"

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:

	float x;
	float y;
	float angle = 180.f;
	float half_size = 20.f;

	float x_speed = 0.f;
	float y_speed = 0.f;

	float speed = 220.f;
	int health = 60;

	Tile* start = nullptr;
	Tile* finish = nullptr;
	std::vector<Tile*> path;

	sf::Clock animation_clock;
	int animation_speed = 65;
	int frame_count = 0;

	sf::Sprite enemy_sprite;
	std::vector<sf::Texture> enemy_frames;

	sf::FloatRect hitbox;

public:

	Enemy(float x_, float y_, std::vector<sf::Texture>& enemy_frames_);

	void die(sf::Texture& body_texture);

	bool checkCollision(float bullet_x, float bullet_y);

	void seekPlayer(Tile* start, Tile* finish, std::vector<std::vector<Tile>>& tiles);

	void update(std::vector<Enemy>& all_enemies, float dt);

	sf::Sprite getSprite();

	float getX() const;
	float getY() const;

	int getHealth(int damege);

	bool checkCollision(float player_x, float player_y) const;

	void setTexture(sf::Texture& new_texture);

	sf::FloatRect getHitbox();

};

#endif