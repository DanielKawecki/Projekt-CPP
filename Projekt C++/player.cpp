#include <SFML/Graphics.hpp>
#include "player.h"
#include "bullet.h"
#include "application.h"
#include <cmath>
#include <cstdlib>

Player::Player(MyApplication& App_) : App(App_) {
	shot_cooldown = sf::seconds(60.f) / firerate;

	player_sprite.setTexture(App.getPlayerSprite());
	player_sprite.scale(3.f, 3.f);
	player_sprite.setOrigin(13.f, 10.f);
}

Player::~Player() {}

sf::Sprite Player::draw() {
	player_sprite.setPosition(sf::Vector2f(x, y));
	player_sprite.setRotation(angle);
	return player_sprite;
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		shoot();
}

void Player::look(sf::RenderWindow &window) {
	angle = atan2((sf::Mouse::getPosition(window).y - y), (sf::Mouse::getPosition(window).x - x)) * 180.f / M_PI;
}

void Player::shoot() {
	if (shot_clock.getElapsedTime() >= shot_cooldown) {
		App.createBullet(x, y, angle, 0);
		shot_clock.restart();
	}
}
