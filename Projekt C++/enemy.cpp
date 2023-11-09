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

sf::Sprite Enemy::getSprite() {
	return enemy_sprite;
}

float Enemy::getX() const {
	return x;
}

float Enemy::getY() const {
	return y;
}
