#include <SFML/Graphics.hpp>

#ifndef ENEMY_H
#define ENEMY_H

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

class Enemy {
private:

	float x;
	float y;
	float angle = 180.f;

	float x_speed = 0.f;
	float y_speed = 0.f;

	float speed = 100.f;
	int health = 100;

	sf::Sprite enemy_sprite;

public:

	Enemy(float x_, float y_, sf::Texture& enemy_texture);

	void die(sf::Texture& body_texture);

	bool checkCollision(float bullet_x, float bullet_y);

	void seekPlayer(float player_x, float player_y);

	void update(std::vector<Enemy>& all_enemies, float dt);

	sf::Sprite getSprite();

	float getX() const;
	float getY() const;

	int getHealth(int damege);

};

#endif