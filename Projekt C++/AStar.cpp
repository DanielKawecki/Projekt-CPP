#include <vector>
#include <iostream>
#include "AStar.h"
#include "tile.h"

AStar::AStar(std::vector<std::vector<Tile>>& tiles_) : tiles(tiles_) {}

std::vector<Tile*> AStar::findPath(Tile* start, Tile* finish) {
	std::vector<Tile*> path;

	std::priority_queue<Tile*, std::vector<Tile*>, decltype(&AStar::compare)> openSet;

	start->setCosts(0.f, distance(start, finish), distance(start, finish));
	openSet.push(start);

	while (!openSet.empty()) {
		Tile* current = openSet.top();
		openSet.pop();

		if (current == finish) {
			while (current != nullptr) {
				path.push_back(current);
				current = current->getParent();
			}
			break;
		}

		for (Tile* neighbor : current->getNeighbors()) {
			float tentativeG = current->getCosts()[0] + distance(current, neighbor);
			std::cout << tentativeG << "\n";

			if (tentativeG < neighbor->getCosts()[0]) {
				neighbor->setParent(current);
				neighbor->setCosts(tentativeG, distance(neighbor, finish), tentativeG + distance(neighbor, finish));

				if (!openSetContains(openSet, neighbor)) {
					openSet.push(neighbor);
				}
			}
		}
	}

	std::reverse(path.begin(), path.end());
	return path;
}

float AStar::distance(Tile* a, Tile* b) {
	return std::sqrt(std::pow(b->getX() - a->getX(), 2) + std::pow(b->getY() - a->getY(), 2));
}

bool AStar::compare(Tile* a, Tile* b) {
	return a->getCosts()[2] > b->getCosts()[2];
}

bool AStar::openSetContains(std::priority_queue<Tile*, std::vector<Tile*>, decltype(&compare)>& openSet, Tile* tile) {
	std::vector<Tile*> temp;
	bool found = false;

	while (!openSet.empty()) {
		temp.push_back(openSet.top());
		if (compare(openSet.top(), tile)) {
			found = true;
		}
		openSet.pop();
	}

	for (Tile* t : temp) {
		openSet.push(t);
	}

	return found;
}