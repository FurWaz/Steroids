#pragma once
#include <vector>
#include "Particle.h"
#include "BackParticle.h"
#include "GameManager.h"

class ParticleManager
{
private:
	std::vector<Particle*> particles;
	BackParticle* backParticles[200];
	GameManager* gm;
	void addBackParticle(int index);

public:
	static const int NB_BACKPARTICLES = 200;
	ParticleManager(GameManager& gm);
	void addCrushParticles(sf::Vector2f pos);
	void addKickParticles(sf::Vector2f pos);
	void update(float dt);
	std::vector<Particle*> getParticles();
	BackParticle** getBackParticles();
};