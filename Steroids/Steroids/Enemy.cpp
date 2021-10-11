#include "Enemy.h"

Enemy::Enemy() : Entity()
{

}

Enemy::Enemy(sf::Vector2f pos, float speed, float direction, float size) : Entity(pos, speed, direction, size)
{

}

void Enemy::setPlayerPos(sf::Vector2f pos)
{
	this->playerPos = pos;
}

void Enemy::update(float dt)
{
	this->setDirection(std::atan2(
		this->playerPos.y - this->pos.y,
		this->playerPos.x - this->pos.x
	) - 1.5707963);

	this->tarVel = this->dir;
	this->tarVel *= this->speed;
	this->curVel += (this->tarVel - this->curVel) * (dt / this->smoothness);
	float dx = this->playerPos.x - this->pos.x;
	float dy = this->playerPos.y - this->pos.y;
	if (std::sqrt(dx*dx + dy*dy) > this->size)
		this->pos += this->curVel * dt;
}

sf::Sprite Enemy::draw(float dt)
{
	this->renderTex.clear(sf::Color::Transparent);
	sf::ConvexShape shape(4);
	shape.setPoint(0, sf::Vector2f(0, this->size));
	shape.setPoint(1, sf::Vector2f(this->size / 2, 0));
	shape.setPoint(2, sf::Vector2f(this->size, this->size));
	shape.setPoint(3, sf::Vector2f(this->size / 2, this->size / 2));
	shape.setFillColor(sf::Color::Red);
	this->renderTex.draw(shape);
	this->sprite.setPosition(this->pos);
	this->sprite.setRotation((this->direction * 180.f) / 3.1415926f);
	return this->sprite;
}

void Enemy::shoot()
{
	this->bullets.push_back(new Bullet(this->pos + this->dir * (this->size / 2), this->curVel, 350.f, this->direction, 10.f));
}