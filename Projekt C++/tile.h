#include <SFML/Graphics.hpp>
#include <vector>

#ifndef TILE_H
#define TILE_H

class Tile {
private:
	float x;
	float y;
	float size = 65;

	bool wall = false;
	bool spawn = false;

	sf::Sprite tile_sprite;
	std::vector<Tile*> neighbors;
	
	Tile* parent;

public:
	Tile(float x_, float y_, sf::Texture& tile_texture, bool is_wall, bool is_spawn);

	sf::Sprite getSprite();

	bool checkCollision(float bullet_x, float bullet_y) const;

	float getX();
	float getY();
	bool isWall() const;
	bool isSpawn() const;
	void addNeighbor(Tile* neighbor);
	Tile* getParent();
	std::vector<Tile*> getNeighbors();
	void setParent(Tile* parent_);
	void setAsMarked();

};

#endif 

