#include <SFML/Graphics.hpp>
#include <cmath>
#include "bullet.h"
#include "application.h"

Bullet::Bullet(float x_, float y_, float angle_, int damage_) {
	x = x_;
	y = y_;
	angle = angle_;
	damage = damage_;

	bulllet_shape.setSize(sf::Vector2f(40, 5));
	bulllet_shape.setOrigin(sf::Vector2f(20, 2.5));
	bulllet_shape.rotate(angle_);
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

sf::RectangleShape Bullet::draw() {
	bulllet_shape.setPosition(sf::Vector2f(x, y));
	return bulllet_shape;
}