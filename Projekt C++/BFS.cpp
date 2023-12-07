#include "BFS.h"
#include "tile.h"

BFS::BFS(std::vector<std::vector<Tile>>& tiles_) : tiles(tiles_) {}

std::vector<Tile*> BFS::findPath(Tile* start, Tile* finish) {

	openSet.push(start);
	closeSet.insert(start);

	while (!openSet.empty()) {
		Tile* current = openSet.front();
		openSet.pop();

		if (current == finish) {
			while (current != nullptr) {
				path.push_back(current);
				current = current->getParent();
			}
			break;
		}

		for (Tile* neighbor : current->getNeighbors()) {
			if (closeSet.find(neighbor) == closeSet.end()) {
				neighbor->setParent(current);
				if (!neighbor->isWall())
					openSet.push(neighbor);
				closeSet.insert(neighbor);
			}
		}
	}

	std::reverse(path.begin(), path.end());
	return path;
}