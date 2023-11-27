#include <SFML/Graphics.hpp>
#include "tile.h"

Tile::Tile(float x_, float y_, sf::Texture& tile_texture_, bool is_wall) {
	x = x_;
	y = y_;

	wall = is_wall;

	tile_sprite.setTexture(tile_texture_);
	tile_sprite.setPosition(x_, y_);
	tile_sprite.setScale(2.f, 2.f);
}

sf::Sprite Tile::getSprite() {
	return tile_sprite;
}