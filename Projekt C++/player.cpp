#include <SFML/Graphics.hpp>
#include "player.h"
#include "bullet.h"
#include "application.h"
#include "tile.h"
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

sf::Sprite Player::getLegsSprite() {
	legs_sprite.setPosition(x, y);
	legs_sprite.setRotation(angle);
	legs_sprite.setOrigin(16.f, 16.f);
	
	sf::Sprite scaled_legs_sprite = legs_sprite;
	scaled_legs_sprite.scale(3.f, 3.f);

	return scaled_legs_sprite;
}

void Player::move(float dt, std::vector<Tile>& all_tiles) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		speed_x -= acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		speed_x += acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		speed_y -= acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		speed_y += acceleration * dt;

	if (!App.mapCollision(x + speed_x * dt, y + speed_y * dt)) {
		x += speed_x * dt;
		y += speed_y * dt;
	}

	else if (!App.mapCollision(x + speed_x * dt, y)) {
		x += speed_x * dt;
	}

	else if (!App.mapCollision(x, y + speed_y * dt)) {
		y += speed_y * dt;
	}

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

	if (abs(speed_x) > 10.0 || abs(speed_y) > 10.0)
		is_moving = true;
	else
		is_moving = false;

	if (is_moving && animation_clock.getElapsedTime().asMilliseconds() >= animation_speed) {
		frame_count = (frame_count + 1) % 14;
		legs_sprite.setTexture(App.getLegSprite(frame_count));
		animation_clock.restart();
	}
	else if(!is_moving)
		legs_sprite.setTexture(App.getLegSprite(7));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		shoot();
}

void Player::look(sf::RenderWindow& window, sf::View& view) {
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f world_mouse_position = window.mapPixelToCoords(mouse_position, view);
	angle = atan2((world_mouse_position.y - y), (world_mouse_position.x - x)) * 180.f / M_PI;
}

void Player::shoot() {
	if (shot_clock.getElapsedTime() >= shot_cooldown) {
		App.createBullet(x, y, angle, 0);
		shot_clock.restart();
	}
}

float Player::getX() const {
	return x;
}

float Player::getY() const {
	return y;
}

void Player::checkEnemies(std::vector<Enemy> all_enemies) {

}
