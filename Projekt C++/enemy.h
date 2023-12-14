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

	float x_speed = 0.f;
	float y_speed = 0.f;

	float speed = 200.f;
	int health = 50;

	Tile* start = nullptr;
	Tile* finish = nullptr;
	std::vector<Tile*> path;

	sf::Sprite enemy_sprite;

public:

	Enemy(float x_, float y_, sf::Texture& enemy_texture);

	void die(sf::Texture& body_texture);

	bool checkCollision(float bullet_x, float bullet_y);

	void seekPlayer(Tile* start, Tile* finish, std::vector<std::vector<Tile>>& tiles);

	void update(std::vector<Enemy>& all_enemies, float dt);

	sf::Sprite getSprite();

	float getX() const;
	float getY() const;

	int getHealth(int damege);

};

#endif