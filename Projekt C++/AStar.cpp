#include <vector>
#include "AStar.h"
#include "tile.h"

AStar::AStar(std::vector<std::vector<Tile>>& tiles_) : tiles(tiles_) {}

std::vector<Tile*> AStar::findPath(Tile* start, Tile* finish) {
	std::vector<Tile*> path;

	auto compare = [](Tile* a, Tile* b) {
		return a->getCosts()[2] > b->getCosts()[2];
		};

	std::priority_queue<Tile*, std::vector<Tile*>, decltype(compare)> openSet(compare);

	start->setCosts(0.f, distance(start, finish), distance(start, finish));
	openSet.push(start);

	while (!openSet.empty()) {
		Tile* current = openSet.top();
		openSet.pop();

		if (current == finish) {

		}
	}
}

float AStar::distance(Tile* a, Tile* b) {
	return std::sqrt(std::pow(b->getX() - a->getX(), 2) + std::pow(b->getY() - a->getY(), 2));
}