#pragma once
#include <vector>
#include "Particle.h"

class ParticleManager
{
private:
	std::vector<Particle*> particles;

public:
	ParticleManager();
	void addCrushParticles(sf::Vector2f pos);
	void update(float dt);
	std::vector<Particle*> getParticles();
};