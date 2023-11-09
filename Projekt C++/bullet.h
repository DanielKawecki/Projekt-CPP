#include <SFML/Graphics.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
	Bullet(float x_, float y_, float angle_, int damage, sf::Texture& bullet_texture);
	
	~Bullet();

	void update(float dt);

	float getX() const;
	float getY() const;
	float getAngle() const;

	sf::Sprite getSprite();

private:
	float x = 0;
	float y = 0;
	float speed = 1200;
	float angle;
	int damage;

	sf::Sprite bullet_sprite;

};

#endif
