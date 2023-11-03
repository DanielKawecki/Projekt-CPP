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

	sf::Sprite getSprite();

};

#endif