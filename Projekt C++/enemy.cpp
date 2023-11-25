#include <iostream>
#include <SFML/Graphics.hpp>
#include "enemy.h"

Enemy::Enemy(float x_, float y_, sf::Texture& enemy_texture) {
	x = x_;
	y = y_;

	enemy_sprite.setTexture(enemy_texture);
	enemy_sprite.scale(3.f, 3.f);
	enemy_sprite.setOrigin(13.f, 10.f);
	enemy_sprite.setRotation(angle);
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

void Enemy::seekPlayer(float player_x, float player_y) {
	angle = atan2((player_y - y), (player_x - x)) * (180.f / M_PI);
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

	//std::cout << separation.x << "\t" << separation.y << "\n";

	x_speed = speed * cos(angle * M_PI / 180.f);
	y_speed = speed * sin(angle * M_PI / 180.f);

	x_speed += (separation.x * 50);
	y_speed += (separation.y * 50);

	x += x_speed * dt;
	y += y_speed * dt;

}

sf::Sprite Enemy::getSprite() {
	enemy_sprite.setPosition(x, y);
	enemy_sprite.setRotation(angle);
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
