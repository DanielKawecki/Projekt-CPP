#include <SFML/Graphics.hpp>
#include "player.h"
#include "bullet.h"
#include "application.h"
#include "tile.h"
#include <cmath>
#include <cstdlib>

Player::Player(MyApplication& App_) : App(App_) {
	x = initial_x;
	y = initial_y;

	shot_cooldown = sf::seconds(60.f) / firerate;

	player_sprite.setTexture(App.getPlayerSprite());
	player_sprite.scale(3.f, 3.f);
	player_sprite.setOrigin(12.f, 5.f);

	reload_rect.setFillColor(sf::Color::White);
	reload_rect.setPosition(sf::Vector2f(100.f, 100.f));
	reload_rect.setOutlineColor(sf::Color::Black);
	reload_rect.setOutlineThickness(2.f);
}

Player::~Player() {}

sf::Sprite Player::draw() {
	if (angle > -90.f && angle < 90.f)
		player_sprite.setScale(3.f, 3.f);
	else
		player_sprite.setScale(3.f, -3.f);

	player_sprite.setPosition(sf::Vector2f(x, y));
	player_sprite.setRotation(angle);
	return player_sprite;
}

sf::Sprite Player::getLegsSprite() {
	legs_sprite.setPosition(x, y);
	legs_sprite.setOrigin(16.f, 16.f);
	
	sf::Sprite scaled_legs_sprite = legs_sprite;
	
	if (angle > -90.f && angle < 90.f)
		scaled_legs_sprite.setScale(3.f, 3.f);
	else
		scaled_legs_sprite.setScale(-3.f, 3.f);

	return scaled_legs_sprite;
}

void Player::move(float dt, std::vector<Tile>& all_tiles, std::vector<Enemy>& all_enemies) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) 
		speed_x -= acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) 
		speed_x += acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		speed_y -= acceleration * dt;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		speed_y += acceleration * dt;

	float new_pos_x = x + speed_x * dt;
	float new_pos_y = y + speed_y * dt;

	if (!App.mapCollision(new_pos_x, new_pos_y) && !App.enemyCollision(new_pos_x, new_pos_y)) {
		x += speed_x * dt;
		y += speed_y * dt;
	}

	else if (!App.mapCollision(new_pos_x, y) && !App.enemyCollision(new_pos_x, y)) {
		x += speed_x * dt;
	}

	else if (!App.mapCollision(x, new_pos_y) && !App.enemyCollision(x, new_pos_y)) {
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
		frame_count = (frame_count + 1) % 12;
		legs_sprite.setTexture(App.getLegSprite(frame_count));
		animation_clock.restart();
	}
	else if(!is_moving)
		legs_sprite.setTexture(App.getLegSprite(0));

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mag > 0 && !reloading)
		shoot();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && mag < mag_size) {
		reloading = true;
		reload_clock.restart();
		reload_rect.setSize(sf::Vector2f(100.f, 4.f));
	}

	if (reloading == true && reload_clock.getElapsedTime().asSeconds() >= reload_time) {
		reload();
		reload_rect.setSize(sf::Vector2f(0.f, 0.f));
	}
	else if (reloading == true) {
		float ratio = reload_clock.getElapsedTime().asSeconds() / reload_time;
		int length = ceil(ratio * 100);
		reload_rect.setSize(sf::Vector2f(100 - length, 4.f));
	}
}

void Player::look(sf::RenderWindow& window, sf::View& view) {
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);
	sf::Vector2f world_mouse_position = window.mapPixelToCoords(mouse_position, view);
	angle = atan2((world_mouse_position.y - y), (world_mouse_position.x - x)) * 180.f / M_PI;
	reload_rect.setPosition(sf::Vector2f(mouse_position.x - 50, mouse_position.y + 30));
}

void Player::shoot() {
	if (shot_clock.getElapsedTime() >= shot_cooldown) {
		App.createBullet(x, y, angle, 0);
		shot_clock.restart();
		mag -= 1;
	}
}

float Player::getX() const {
	return x;
}

float Player::getY() const {
	return y;
}

void Player::checkEnemies() {
	if (App.enemyCollision(x, y) && damage_clock.getElapsedTime() >= damage_cooldown && health > 0) {
		health -= 5;
		damage_clock.restart();
	}
}

int Player::getHealth() const {
	return health;
}

void Player::setHealth(int health_) {
	health = health_;
}

void Player::resetPos() {
	x = initial_x;
	y = initial_y;
}

void Player::reload() {
	int difference = mag_size - mag;

	if (difference > ammo) {
		mag += ammo;
		ammo = 0;
	}
	else {
		ammo -= difference;
		mag = mag_size;
	}
	reloading = false;
		
}

std::vector<int> Player::getAmmo() {
	std::vector<int> ammo_vector;
	ammo_vector.push_back(mag);
	ammo_vector.push_back(ammo);
	return ammo_vector;
}

sf::RectangleShape Player::getReloadRect() {
	return reload_rect;
}
