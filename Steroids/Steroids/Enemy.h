#pragma once
#include "Entity.h"
#include "Bullet.h"

class Enemy : public Entity
{
private:
	sf::Vector2f playerPos;
	float speedFactor = 1;

public:
	std::vector<Bullet*> bullets;

	Enemy();
	Enemy(sf::Vector2f pos, float speed = 1, float direction = 0, float size = 1);

	void update(float dt);
	sf::Sprite draw(float dt);
	void setPlayerPos(sf::Vector2f pos);
	void shoot();
	void setSpeedFactor(float factor);
};