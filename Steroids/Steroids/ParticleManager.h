#pragma once
#include <vector>
#include "Particle.h"
#include "GameManager.h"

class ParticleManager
{
private:
	std::vector<Particle*> particles;
	std::vector<Particle*> backParticles;

public:
	ParticleManager();
	void addCrushParticles(sf::Vector2f pos);
	void addKickParticles(sf::Vector2f pos);
	void update(float dt, GameManager gm);
	std::vector<Particle*> getParticles();
};