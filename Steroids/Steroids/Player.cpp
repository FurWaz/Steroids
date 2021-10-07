#include "Player.h"

Player::Player(): Entity()
{

}

Player::Player(sf::Vector2f pos, float speed, float direction, float size): Entity(pos, speed, direction, size)
{
	
}

void Player::setMousePos(sf::Vector2i mPos)
{
	this->mPos = mPos;
}

void Player::setKeys(bool* keys)
{
	for (unsigned char i = 0; i < 4; i++)
		this->keys[i] = keys[i];
}

void Player::update(float dt)
{
	this->setDirection(std::atan2(
		this->mPos.y - this->pos.y,
		this->mPos.x - this->pos.x
	) - 1.5707963);

	this->tarVel = sf::Vector2f(
		(this->keys[2] ? 1 : 0) - (this->keys[3] ? 1 : 0),
		(this->keys[1] ? 1 : 0) - (this->keys[0] ? 1 : 0)
	);
	// normalize movements
	float length = std::sqrt(this->tarVel.x * this->tarVel.x + this->tarVel.y * this->tarVel.y);
	if (length != 0) this->tarVel /= length;
	this->tarVel *= this->speed;
	this->curVel += (this->tarVel - this->curVel) * ( dt / this->smoothness);
	this->pos += this->curVel * dt;
}

sf::Sprite Player::draw(float dt)
{
	this->renderTex.clear(sf::Color::Transparent);
	sf::ConvexShape shape(4);
	shape.setPoint(0, sf::Vector2f(0, this->size));
	shape.setPoint(1, sf::Vector2f(this->size/2, 0));
	shape.setPoint(2, sf::Vector2f(this->size, this->size));
	shape.setPoint(3, sf::Vector2f(this->size / 2, this->size/2));
	shape.setFillColor(sf::Color::Blue);
	this->renderTex.draw(shape);
	this->sprite.setPosition(this->pos);
	this->sprite.setRotation((this->direction * 180.f) / 3.1415926f);
	return this->sprite;
}

void Player::shoot()
{
	this->bullets.push_back(new Bullet(this->pos+this->dir*(this->size / 2), sf::Vector2f(), 350.f, this->direction, 10.f));
}