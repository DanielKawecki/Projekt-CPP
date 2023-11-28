#include <SFML/Graphics.hpp>

#ifndef TILE_H
#define TILE_H

class Tile {
private:
	float x;
	float y;

	bool wall = false;

	float size = 65;

	sf::Sprite tile_sprite;

public:
	Tile(float x_, float y_, sf::Texture& tile_texture, bool is_wall);

	sf::Sprite getSprite();

	bool checkCollision(float bullet_x, float bullet_y) const;

	float getX();
	float getY();
	bool isWall() const;

};

#endif 

