#include "ParticleManager.h"

ParticleManager::ParticleManager()
{

}

void ParticleManager::addCrushParticles(sf::Vector2f pos)
{
	for (int i = 0; i < 10; i++) // enemy particles
	{
		this->particles.push_back(new Particle(
			pos,
			sf::Color::Red,
			rand() * 0.01f,
			(rand() % 100 + 100) / 200.f,
			(rand() % 100 + 100) / 10.f,
			rand() % 100 + 100
		));
	}
	for (int i = 0; i < 5; i++) // bullet particles
	{
		this->particles.push_back(new Particle(
			pos,
			sf::Color::Green,
			rand() * 0.01f,
			(rand() % 100 + 100) / 200.f,
			(rand() % 100 + 100) / 30.f,
			rand() % 50 + 20
		));
	}
}

void ParticleManager::update(float dt)
{
	for (int i = 0; i < this->particles.size(); i++)
	{
		Particle* p = this->particles[i];
		p->update(dt);
		if (p->getCounter() >= p->getLifetime())
		{
			this->particles.erase(this->particles.begin() + i);
			delete p;
		}
	}
}

std::vector<Particle*> ParticleManager::getParticles()
{
	return this->particles;
}