#include "Particle.h"

Particle::Particle()
{
	this->init(sf::Vector2f(), sf::Color::Red, 0, 100.f, 20.f, 200.f);
}

Particle::Particle(sf::Vector2f pos, sf::Color color, float dir, float lifeTime, float size, float speed)
{
	this->init(pos, color, dir, lifeTime, size, speed);
}

void Particle::init(sf::Vector2f pos, sf::Color color, float dir, float lifeTime, float size, float speed)
{
	this->pos = pos;
	this->dir = sf::Vector2f(-std::sin(dir), std::cos(dir));
	this->initSize = size;
	this->initSpeed = speed;
	this->renderTex.create(size, size);
	this->sprite.setTexture(this->renderTex.getTexture());
	this->circle = sf::CircleShape(size/2, 8);
	this->counter = 0;
	this->lifeTime = lifeTime;
	this->color = color;
}

void Particle::update(float dt)
{
	this->counter += dt;
	float factor = (this->lifeTime - this->counter) / this->lifeTime;
	this->curSize = this->initSize * factor;
	this->curSpeed = this->initSpeed * factor;
	this->pos += this->dir * this->curSpeed * dt;
	this->circle.setRadius(this->curSize/2);
	this->sprite.setPosition(this->pos);
	this->color.a = factor * 255;
	this->circle.setFillColor(this->color);
}

sf::Sprite Particle::draw(float dt)
{
	this->renderTex.clear(sf::Color::Transparent);
	this->renderTex.draw(this->circle);
	this->renderTex.display();
	return this->sprite;
}

float Particle::getCounter()
{
	return this->counter;
}

float Particle::getLifetime()
{
	return this->lifeTime;
}

sf::Vector2f Particle::getPos()
{
	return this->pos;
}