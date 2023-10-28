#include <SFML/Graphics.hpp>
#include <cmath>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
	Bullet(float x_, float y_, float angle_, int damage);
	
	~Bullet();

	void update(float dt);

	sf::RectangleShape draw();

private:
	float x = 0;
	float y = 0;
	float speed = 1200;
	float angle;
	int damage;

	sf::RectangleShape bulllet_shape;

};

#endif
