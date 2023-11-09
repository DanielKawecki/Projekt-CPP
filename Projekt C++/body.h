#include <SFML/Graphics.hpp>

#ifndef BODY_H
#define BODY_H

class Body {
private:
	float x;
	float y;

	sf::Sprite body_sprite;

	sf::Clock exist_clock;
	sf::Time exist_time;

public:
	Body(float x_, float y_, float angle_, sf::Texture& body_texture);

	sf::Sprite getSprite();

	bool checkExixtTime();
};

#endif 
