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
		x -= 400 * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		x += 400 * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		y -= 400 * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		y += 400 * dt;
}