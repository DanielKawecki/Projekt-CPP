#include <SFML/Graphics.hpp>
#include "tile.h"

Tile::Tile(float x_, float y_, sf::Texture& tile_texture_, bool is_wall, bool is_spawn) {
	x = x_;
	y = y_;

	wall = is_wall;
	spawn = is_spawn;
	parent = nullptr;

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

bool Tile::isWall() const {
	return wall;
}

bool Tile::isSpawn() const {
	return spawn;
}

void Tile::addNeighbor(Tile* neighbor) {
	neighbors.push_back(neighbor);
}

Tile* Tile::getParent() {
	return parent;
}

std::vector<Tile*> Tile::getNeighbors() {
	return neighbors;
}

void Tile::setParent(Tile* parent_) {
	parent = parent_;
}

void Tile::setAsMarked() {
	tile_sprite.setColor(sf::Color::Black);
}

bool Tile::checkRefil() {
	if (refil_clock.getElapsedTime() >= refil_time) {
		refil_clock.restart();
		return true;
	}
		

	return false;
}

