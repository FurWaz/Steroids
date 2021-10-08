#pragma once
#include <SFML/Graphics.hpp>

class Particle
{
private:
	sf::Vector2f pos;
	float size;
	float speed;
	sf::CircleShape circle;
	sf::RenderTexture renderTex;
	sf::Sprite sprite;

	void init(sf::Vector2f pos, float size, float speed);

public:
	Particle();
	Particle(sf::Vector2f pos, float size = 1.f, float speed = 200.f);
	void update(float dt);
	sf::Sprite draw(float dt);
};