#include <SFML/Graphics.hpp>
#include "player.h"

Player::Player() {}

Player::~Player() {}

sf::CircleShape Player::draw() {
	return player_shape;
}