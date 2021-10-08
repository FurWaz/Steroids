#pragma once
#include "Entity.h"
#include "Bullet.h"
#include <vector>

class Player : public Entity
{
private:
	sf::Vector2i mPos;
	int life = 100;
	bool keys[4] = { false, false, false, false };

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
	int getLife();
};