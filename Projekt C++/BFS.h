#include <vector>
#include <queue>
#include <unordered_set>
#include "tile.h"

#ifndef BFS_H
#define BFS_H

class BFS {
private:
	std::vector<std::vector<Tile>> tiles;
	std::vector<Tile*> path;
	std::queue<Tile*> openSet;
	std::unordered_set<Tile*> closeSet;

public:
	BFS(std::vector<std::vector<Tile>>& tiles_);

	std::vector<Tile*> findPath(Tile* start, Tile* finish);
};


#endif
