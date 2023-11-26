#include <SFML/Graphics.hpp>
#include "tile.h"

Tile::Tile(float x_, float y_, sf::Texture& tile_texture_) {
	x = x_;
	y = y_;

	tile_sprite.setTexture(tile_texture_);
	tile_sprite.setPosition(x_, y_);
	tile_sprite.setScale(3.f, 3.f);
}

sf::Sprite Tile::getSprite() {
	return tile_sprite;
}