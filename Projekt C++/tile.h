#include <SFML/Graphics.hpp>

#ifndef TILE_H
#define TILE_H

class Tile {
private:
	float x;
	float y;

	sf::Vector2i size = sf::Vector2i(48, 48);

	sf::Sprite tile_sprite;

public:
	Tile(float x_, float y_, sf::Texture& tile_texture);

	sf::Sprite getSprite();

};

#endif 

