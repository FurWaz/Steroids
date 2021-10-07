#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class Entity
{
protected:
	sf::Vector2f pos;
	sf::Vector2f dir;
	sf::Vector2f curVel; // current velocity
	sf::Vector2f tarVel; // target velocity
	float speed;
	float direction;
	float size;
	float smoothness;

	sf::Sprite sprite;
	sf::RenderTexture renderTex;

	void init(sf::Vector2f pos = sf::Vector2f(), float speed = 1, float direction = 0, float size = 1);

public:
	Entity();
	Entity(sf::Vector2f pos, float speed = 1, float direction = 0, float size = 1);

	virtual void update(float dt);
	virtual sf::Sprite draw(float dt);
	
	void setSpeed(float speed);
	void setDirection(float direction);
	void setSize(float size);
	void setPos(sf::Vector2f pos);

	float getSpeed();
	float getDirection();
	float getSize();
	sf::Vector2f getDirectionVector();
	sf::Vector2f getPos();

	bool collides(Entity* en);
	void moveBy(sf::Vector2f pos);
};