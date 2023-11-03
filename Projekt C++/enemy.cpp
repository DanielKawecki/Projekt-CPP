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

sf::Sprite Enemy::getSprite() {
	return enemy_sprite;
}
