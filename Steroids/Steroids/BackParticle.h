#pragma once
#include "Particle.h"
class BackParticle : public Particle
{
private:
	int alpha = 0;
	float alphaFactor = 1;
	float scaleFactor = 0;

public:
	BackParticle();
	BackParticle(sf::Vector2f pos, sf::Color color = sf::Color::Red, float dir = 0, float size = 1.f, float speed = 200.f);

	void setAlpha(float factor);
	void setScaleFactor(float factor);
	void update(float dt);
	sf::Sprite draw(float dt);
};