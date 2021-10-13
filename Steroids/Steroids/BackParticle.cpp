#include "BackParticle.h"

BackParticle::BackParticle(): Particle()
{

}

BackParticle::BackParticle(sf::Vector2f pos, sf::Color color, float dir, float size, float speed)
{
	this->alpha = 255;
	this->init(pos, color, dir, 1, size, speed);
}

void BackParticle::setAlpha(float factor)
{
	this->alphaFactor = factor;
}

void BackParticle::setScaleFactor(float factor)
{
	this->scaleFactor = factor;
}

void BackParticle::update(float dt)
{
	this->counter += dt;
	this->curSize = this->initSize * this->scaleFactor;
	this->curSpeed = this->initSpeed * this->scaleFactor;
	this->pos += this->dir * this->curSpeed * dt;
	this->color.a = this->alphaFactor * this->alpha;
	this->sprite.setPosition(this->pos);
	this->sprite.setScale(sf::Vector2f(this->scaleFactor, this->scaleFactor));
	this->circle.setFillColor(this->color);
}

sf::Sprite BackParticle::draw(float dt)
{
	this->renderTex.clear(sf::Color::Transparent);
	this->renderTex.draw(this->circle);
	this->renderTex.display();
	return this->sprite;
}