#include <iostream>
#include <SFML/Graphics.hpp>
#include "enemy.h"
#include "BFS.h"

Enemy::Enemy(float x_, float y_, std::vector<sf::Texture>& enemy_frames_) : enemy_frames(enemy_frames_) {
	x = x_;
	y = y_;

	enemy_sprite.setTexture(enemy_frames[0]);
	enemy_sprite.scale(3.f, 3.f);
	enemy_sprite.setOrigin(13.f, 10.f);
	//enemy_sprite.setRotation(angle);
	enemy_sprite.setPosition(x_, y_);
}

void Enemy::die(sf::Texture& body_texture) {
	enemy_sprite.setTexture(body_texture);
	enemy_sprite.scale(3.f, 3.f);
	enemy_sprite.setOrigin(13.f, 10.f);
	enemy_sprite.setRotation(angle);
	enemy_sprite.setPosition(x, y);
}

bool Enemy::checkCollision(float bullet_x, float bullet_y) {
	return (bullet_x < (x + 20) && bullet_x >(x - 20) && bullet_y < (y + 20) && bullet_y >(y - 20));
}

void Enemy::seekPlayer(Tile* start_, Tile* finish_, std::vector<std::vector<Tile>>& tiles) {
	
	if (start_ != start || finish_ != finish) {
		start = start_;
		finish = finish_;

		BFS bfs(tiles);
		path = bfs.findPath(start, finish);

		if (path.size() >= 2)
			angle = atan2((path[1]->getY() + 32 - y), (path[1]->getX() + 32 - x)) * (180.f / M_PI);

		if (angle > -90.f && angle < 90.f)
			enemy_sprite.setScale(3.f, 3.f);
		else
			enemy_sprite.setScale(-3.f, 3.f);
	}
}

void Enemy::update(std::vector<Enemy>& all_enemies, float dt) {
	sf::Vector2f separation(0.f, 0.f);

	for (auto& other : all_enemies) {
		if (&other != this) {
			sf::Vector2f toOther = sf::Vector2f(other.getX() - x, other.getY() - y);
			float distance = std::hypot(toOther.x, toOther.y);

			if (distance < 100.f)
				separation -= toOther / distance;
		}
	}

	float separationMagnitude = std::hypot(separation.x, separation.y);
	if (separationMagnitude > 0.f) {
		separation /= separationMagnitude;
	}

	x_speed = speed * cos(angle * M_PI / 180.f);
	y_speed = speed * sin(angle * M_PI / 180.f);

	x_speed += (separation.x * 50);
	y_speed += (separation.y * 50);

	x += x_speed * dt;
	y += y_speed * dt;

	if (animation_clock.getElapsedTime().asMilliseconds() >= animation_speed) {
		frame_count = (frame_count + 1) % 12;
		enemy_sprite.setTexture(enemy_frames[frame_count]);
		animation_clock.restart();
	}

}

sf::Sprite Enemy::getSprite() {
	enemy_sprite.setPosition(x, y);
	//enemy_sprite.setRotation(angle);
	return enemy_sprite;
}

float Enemy::getX() const {
	return x;
}

float Enemy::getY() const {
	return y;
}

int Enemy::getHealth(int damage) {
	health -= damage;
	return health;
}

bool Enemy::checkCollision(float player_x, float player_y) const {
	return (player_x > (x - half_size) && player_x < (x + half_size) && player_y > (y - half_size) && player_y < (y + half_size));
}

void Enemy::setTexture(sf::Texture& new_texture) {
	enemy_sprite.setTexture(new_texture);
}
