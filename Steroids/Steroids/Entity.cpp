#include "Entity.h"

Entity::Entity()
{
	this->init();
}

Entity::Entity(sf::Vector2f pos, float speed, float direction, float size)
{
	this->init(pos, speed, direction, size);
}

void Entity::init(sf::Vector2f pos, float speed, float direction, float size)
{
	this->setSpeed(speed);
	this->setDirection(direction);
	this->setSize(size);
	this->setPos(pos);
	this->renderTex.create(this->size, this->size);
	this->sprite.setTexture(this->renderTex.getTexture());
	this->sprite.setOrigin(sf::Vector2f(this->size/2, this->size/2));
	this->smoothness = 0.2f;
}

void Entity::setSpeed(float speed)
{
	this->speed = speed;
}

void Entity::setDirection(float direction)
{
	this->direction = direction;
	this->dir = sf::Vector2f(-std::sin(direction), std::cos(direction));
}

void Entity::setSize(float size)
{
	this->size = size;
}

void Entity::setPos(sf::Vector2f pos)
{
	this->pos = pos;
}

float Entity::getSpeed()
{
	return this->speed;
}

float Entity::getDirection()
{
	return this->direction;
}

float Entity::getSize()
{
	return this->size;
}

sf::Vector2f Entity::getDirectionVector()
{
	return this->dir;
}

sf::Vector2f Entity::getPos()
{
	return this->pos;
}

bool Entity::collides(Entity* en)
{
	float dx = en->pos.x - this->pos.x;
	float dy = en->pos.y - this->pos.y;
	float dist = std::sqrt(dx*dx + dy*dy);
	return dist < (this->size + en->size) / 2;
}

void Entity::update(float dt)
{

}

void Entity::moveBy(sf::Vector2f pos)
{
	this->pos += pos;
}

sf::Sprite Entity::draw(float dt)
{
	this->renderTex.clear(sf::Color(255, 0, 255));
	return this->sprite;
}