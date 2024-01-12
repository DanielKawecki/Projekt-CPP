#include <SFML/Graphics.hpp>
#include "body.h"

Body::Body(float x_, float y_, float angle_, sf::Texture& body_texture) {
	x = x_;
	y = y_;

	body_sprite.setTexture(body_texture);
	body_sprite.setOrigin(16.f, 16.f);
	body_sprite.setPosition(x_, y_);
	

	if (angle_ > -90.f && angle_ < 90.f)
		body_sprite.setScale(-3.f, 3.f);
	else
		body_sprite.setScale(3.f, 3.f);
}

sf::Sprite Body::getSprite() {
	//float new_y = y - (exist_clock.getElapsedTime().asSeconds() / 0.1) * 10;
	//body_sprite.setPosition(x, new_y);

	int alpha = 255 * floor(100*(exist_clock.getElapsedTime().asSeconds() / 0.3));
	body_sprite.setColor(sf::Color(255, 255, 255, alpha));
	return body_sprite;
}

bool Body::checkExixtTime() {
	exist_time = exist_clock.getElapsedTime();
	if (exist_time.asSeconds() > 0.3)
		return true;
	else
		return false;
}