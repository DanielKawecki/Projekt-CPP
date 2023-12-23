#include <SFML/Graphics.hpp>
#include <cmath>
#include "bullet.h"
#include "application.h"

Bullet::Bullet(float x_, float y_, float angle_, int damage_, sf::Texture& bullet_texture) {
	x = x_;
	y = y_;
	angle = angle_;
	damage = damage_;

	bullet_sprite.setTexture(bullet_texture);
	bullet_sprite.scale(2.f, 2.f);
	bullet_sprite.setOrigin(sf::Vector2f(25.f, 3.f));
	bullet_sprite.rotate(angle_);
}

Bullet::~Bullet() {}

void Bullet::update(float dt) {
	x = x + (speed * sin((angle + 90.f) * M_PI / 180.f) * dt);
	y = y + (speed * -cos((angle + 90.f) * M_PI / 180.f) * dt);
}

float Bullet::getX() const {
	return x;
}

float Bullet::getY() const {
	return y;
}

float Bullet::getAngle() const {
	return angle;
}

sf::Sprite Bullet::getSprite() {
	bullet_sprite.setPosition(sf::Vector2f(x, y));
	return bullet_sprite;
}