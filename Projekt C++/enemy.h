#include <SFML/Graphics.hpp>

#ifndef ENEMY_H
#define ENEMY_H

class Enemy {
private:

	float x;
	float y;
	float angle = 180.f;

	sf::Sprite enemy_sprite;

public:

	Enemy(float x_, float y_, sf::Texture& enemy_texture);

	void die(sf::Texture& body_texture);

	bool checkCollision(float bullet_x, float bullet_y);

	sf::Sprite getSprite();

	float getX() const;
	float getY() const;

};

#endif