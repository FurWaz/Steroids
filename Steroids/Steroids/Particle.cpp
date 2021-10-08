#include "Particle.h"

Particle::Particle()
{
	this->init(sf::Vector2f(), 1.f, 200.f);
}

Particle::Particle(sf::Vector2f pos, float size, float speed)
{
	this->init(pos, size, speed);
}

void Particle::init(sf::Vector2f pos, float size, float speed)
{
	this->pos = pos;
	this->size = size;
	this->speed = speed;
	this->renderTex.create(this->size, this->size);
	this->sprite.setTexture(this->renderTex.getTexture());
}

void Particle::update(float dt)
{
	this->size *= 1.001;
	this->speed *= 1.001;
	this->circle = sf::CircleShape(this->size, 8);
}

sf::Sprite Particle::draw(float dt)
{
	return this->sprite;
}