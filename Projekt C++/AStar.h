#include <cmath>
#include <queue>
#include <vector>
#include "tile.h"

#ifndef ASTAR_H
#define ASTAR_H

class AStar {
private:
	std::vector<std::vector<Tile>> tiles;

public:
	AStar(std::vector<std::vector<Tile>>& tiles_);
	std::vector<Tile*> findPath(Tile* start, Tile* finish);
	float distance(Tile* a, Tile* b);
};

#endif
