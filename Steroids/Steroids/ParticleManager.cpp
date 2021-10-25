#include "ParticleManager.h"

ParticleManager::ParticleManager(GameManager& gm)
{
	this->gm = &gm;
	for (int i = 0; i < this->NB_BACKPARTICLES; i++)
		addBackParticle(i);
}

void ParticleManager::addBackParticle(int index)
{
	this->backParticles[index] = new BackParticle(
		sf::Vector2f(this->gm->getScreenSize().x/2, this->gm->getScreenSize().y/2),
		sf::Color::Yellow,
		rand() * 0.01f,
		rand() % 200 + 100,
		rand() % 100 + 50
	);
}

void ParticleManager::addKickParticles(sf::Vector2f pos)
{
	for (int i = 0; i < 10; i++) // enemy particles
	{
		this->particles.push_back(new Particle(
			pos,
			sf::Color::Blue,
			rand() * 0.01f,
			(rand() % 100 + 100) / 200.f,
			(rand() % 100 + 100) / 10.f,
			rand() % 150 + 100
		));
	}
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
	// update entity particles
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

	// update background particles
	float bLvl = this->gm->getSoundInfo()->getBassLevel();
	float lvl = fmin(bLvl + 0.3, 1);
	sf::Vector2u size = this->gm->getScreenSize();
	for (int i = 0; i < this->NB_BACKPARTICLES; i++)
	{
		BackParticle* p = this->backParticles[i];
		if (p == nullptr) continue;
		sf::Vector2f pos = p->getPos();
		
		float dx = size.x/2 - pos.x;
		float dy = size.y/2 - pos.y;
		float distFromCenter = std::sqrt(dx*dx + dy*dy);
		p->setAlpha(lvl);
		p->setScaleFactor(0.5 + bLvl * 0.2 + distFromCenter*2/size.x);
		p->update(dt);

		if (pos.x < 0 || pos.x > this->gm->getScreenSize().x || pos.y < 0 || pos.y > this->gm->getScreenSize().y)
		{
			delete this->backParticles[i];
			this->backParticles[i] = nullptr;
			this->addBackParticle(i);
		}
	}
}

std::vector<Particle*> ParticleManager::getParticles()
{
	return this->particles;
}

BackParticle** ParticleManager::getBackParticles()
{
	return this->backParticles;
}