#include <SFML/Graphics.hpp>
#include "player.h"

Player::Player() {}

Player::~Player() {}

sf::CircleShape Player::draw() {
	player_shape.setPosition(sf::Vector2f(x, y));
	return player_shape;
}

void Player::move(float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		speed_x -= acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		speed_x += acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		speed_y -= acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		speed_y += acceleration * dt;

	x += speed_x * dt;
	y += speed_y * dt;

	if (speed_x > speed_limit)
		speed_x = speed_limit;
	else if (speed_x < -speed_limit)
		speed_x = -speed_limit;

	if (speed_y > speed_limit)
		speed_y = speed_limit;
	else if (speed_y < -speed_limit)
		speed_y = -speed_limit;

	speed_x -= (speed_x > 0 ? friction : (speed_x < 0 ? -friction : 0)) * dt;
	speed_y -= (speed_y > 0 ? friction : (speed_y < 0 ? -friction : 0)) * dt;

}