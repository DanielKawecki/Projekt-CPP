#include <SFML/Graphics.hpp>

#ifndef REFILL_H
#define REFILL_H

class Refill {
private:
	float x;
	float y;

	sf::Sprite refill_sprite;
	sf::FloatRect refill_rect;

public:
	Refill(float x_, float y_, sf::Texture& refill_texture);

	sf::Sprite getSprite();

	sf::FloatRect getRect();
};

#endif 
