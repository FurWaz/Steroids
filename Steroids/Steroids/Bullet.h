#pragma once
#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet();
	Bullet(sf::Vector2f pos, sf::Vector2f vel = sf::Vector2f(), float speed = 1, float direction = 0, float size = 1);
	void update(float dt);
	sf::Sprite draw(float dt);
};