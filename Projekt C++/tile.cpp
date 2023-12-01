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

bool Tile::checkCollision(float bullet_x, float bullet_y) const {
	return (bullet_x > x && bullet_x < (x + size) && bullet_y > y && bullet_y < (y + size));
}

float Tile::getX() {
	return x;
}

float Tile::getY() {
	return y;
}

bool Tile::isWall() const{
	return wall;
}

std::vector<float> Tile::getCosts() {
	return { g, h, f };
}

void Tile::setCosts(float g_, float h_, float f_) {
	g = g_;
	h = h_;
	f = f_;
}