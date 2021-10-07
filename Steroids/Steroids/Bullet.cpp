#include "Bullet.h"

Bullet::Bullet(): Entity()
{
	
}

Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, float speed, float direction, float size): Entity(pos, speed, direction, size)
{
	this->curVel = vel + this->dir * this->speed;
	this->tarVel = vel + this->dir * this->speed;
}

void Bullet::update(float dt)
{
	this->pos += this->tarVel * dt;
}

sf::Sprite Bullet::draw(float dt)
{
	this->renderTex.clear(sf::Color::Transparent);
	sf::CircleShape circle(this->size/2);
	circle.setFillColor(sf::Color::Green);
	this->renderTex.draw(circle);
	this->sprite.setPosition(this->pos);
	return this->sprite;
}