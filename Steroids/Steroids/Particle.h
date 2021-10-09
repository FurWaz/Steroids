#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Particle
{
private:
	sf::Vector2f pos;
	sf::Vector2f dir;
	float initSize;
	float initSpeed;
	float curSize;
	float curSpeed;
	float lifeTime;
	float counter;
	sf::CircleShape circle;
	sf::RenderTexture renderTex;
	sf::Sprite sprite;
	sf::Color color;

	void init(sf::Vector2f pos, sf::Color color, float dir, float lifeTime, float size, float speed);

public:
	Particle();
	Particle(sf::Vector2f pos, sf::Color color = sf::Color::Red, float dir = 0, float lifeTime = 100.f, float size = 1.f, float speed = 200.f);
	virtual void update(float dt);
	sf::Sprite draw(float dt);

	float getCounter();
	float getLifetime();
};