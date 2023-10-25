#include <SFML/Graphics.hpp>
#include "bullet.h"

Bullet::Bullet(float speed_x_, float speed_y_, float angle_, int damage_) {
	speed_x = speed_x_;
	speed_y = speed_y_;
	angle = angle_;
	damage = damage_;

	bulllet_shape.setSize(sf::Vector2f(40, 5));
	bulllet_shape.setOrigin(sf::Vector2f(20, 2.5));
	bulllet_shape.rotate(angle);
}

Bullet::~Bullet() {}