#include <SFML/Graphics.hpp>
#include "body.h"

Body::Body(float x_, float y_, float angle_, sf::Texture& body_texture) {
	x = x_;
	y = y_;

	body_sprite.setTexture(body_texture);
	body_sprite.setOrigin(0.f, 11.f);
	body_sprite.setPosition(x_, y_);
	body_sprite.setScale(3.f, 3.f);
	body_sprite.setRotation(angle_);
}

sf::Sprite Body::getSprite() {
	return body_sprite;
}

bool Body::checkExixtTime() {
	exist_time = exist_clock.getElapsedTime();
	if (exist_time.asSeconds() > 3.f)
		return true;
	else
		return false;
}