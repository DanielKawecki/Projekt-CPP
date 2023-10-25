
#ifndef PLAYER_H
#define PLAYER_H

class Bullet {
public:
	Bullet(float speed_x_, float speed_y_, float angle_, int damage);

	~Bullet();

private:
	float x = 0;
	float y = 0;
	float angle = 0;
	float speed_x;
	float speed_y;
	int damage;

	sf::RectangleShape bulllet_shape;

};

#endif
