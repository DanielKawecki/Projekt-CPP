#include <SFML/Graphics.hpp>
#include "refill.h"

Refill::Refill(float x_, float y_, sf::Texture& refill_texture) {
	x = x_;
	y = y_;

	refill_sprite.setTexture(refill_texture);
	refill_sprite.setPosition(x_, y_);
	refill_sprite.setScale(3.f, 3.f);

	refill_rect.left = x_;
	refill_rect.top = y_;
	refill_rect.width = 30.f;
	refill_rect.height = 30.f;
}

sf::Sprite Refill::getSprite() {
	return refill_sprite;
}

sf::FloatRect Refill::getRect() {
	return refill_rect;
}