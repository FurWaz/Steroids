#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <vector>

class Player : public Entity
{
private:
	sf::Vector2i mPos;
	float maxLife = 50;
	float life = this->maxLife;
	float shootDelta = 0;
	float curSize = 0;
	float tarSize = 1;
	float speedMultiplyer = 1;
	bool keys[4] = { false, false, false, false };
	sf::ConvexShape shape;

public:
	std::vector<Bullet*> bullets;

	Player();
	Player(sf::Vector2f pos, float speed = 1, float direction = 0, float size = 1);

	void setMousePos(sf::Vector2i mPos);
	void setKeys(bool* keys);

	void update(float dt);
	sf::Sprite draw(float dt);
	void shoot();

	void setLife(int life);
	void kick(float force = 1);
	void setSize(float size);

	void setMovement(sf::Vector2f move);
	void setSpeed(float speed);

	int getLife();
	int getMaxLife();
};