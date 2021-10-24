#include "UIElement.h"
#include <math.h>

UIElement::UIElement()
{
	this->setDimensions(sf::FloatRect(0, 0, 100, 100));
	this->init();
}

UIElement::UIElement(sf::FloatRect dims)
{
	this->setDimensions(dims);
	this->init();
}

void UIElement::init()
{
	this->moveX_s = (rand() % 50 + 50) * 0.001;
	this->moveY_s = (rand() % 50 + 50) * 0.001;
	this->rot_s   = (rand() % 50 + 50) * 0.001;
	this->moveX = this->moveX_s * 100;
	this->moveY = this->moveY_s * 100;
	this->rot = this->rot_s * 100;
}

void UIElement::resizeTextures()
{
	this->renderTex.create(this->dims.width, this->dims.height);
	this->sprite.setTexture(this->renderTex.getTexture());
	this->sprite.setOrigin(this->dims.width / 2, this->dims.height / 2);
}


void UIElement::setPos(sf::Vector2f pos)
{
	this->dims.left = pos.x;
	this->dims.top = pos.y;
	this->sprite.setPosition(this->getPos());
}

void UIElement::setSize(sf::Vector2f size)
{
	this->dims.width = size.x;
	this->dims.height = size.y;
	this->resizeTextures();
}

void UIElement::setDimensions(sf::FloatRect dims)
{
	this->dims = dims;
	this->resizeTextures();
	this->sprite.setPosition(this->getPos());
}

sf::Vector2f UIElement::getPos()
{
	return sf::Vector2f(this->dims.left, this->dims.top);
}

sf::Vector2f UIElement::getSize()
{
	return sf::Vector2f(this->dims.width, this->dims.height);
}

sf::FloatRect UIElement::getDimensions()
{
	return this->dims;
}

bool UIElement::isHovered()
{
	return this->hovered;
}

bool UIElement::isClicked()
{
	return this->clicked;
}

bool UIElement::collides(UIElement& other)
{
	return this->dims.intersects(other.dims);
}
bool UIElement::collides(sf::Vector2i pos)
{
	return pos.x >= this->dims.left - this->dims.width/2  &&
		   pos.x <  this->dims.left + this->dims.width/2  &&
		   pos.y >= this->dims.top  - this->dims.height/2 &&
		   pos.y <  this->dims.top  + this->dims.height/2;
}

void UIElement::onHover(bool state)
{
	this->hovered = state;
}

void UIElement::onScroll(float amount)
{
	
}

void UIElement::onClick(bool state)
{
	this->clicked = state;
}

void UIElement::update(float dt)
{
	std::vector<UIElement*> elems = this->getElements();
	for (unsigned int i = 0; i < elems.size(); i++)
		elems[i]->update(dt);

	moveX += moveX_s;
	moveY += moveY_s;
	rot += rot_s;

	this->sprite.setPosition(
		this->getPos() +
		sf::Vector2f(cos(moveX)*3, cos(moveY)*3)
	);
	this->sprite.setRotation(cos(rot));
}

std::vector<UIElement*> UIElement::getElements()
{
	return std::vector<UIElement*>();
}

sf::Sprite UIElement::draw(float dt)
{
	return this->sprite;
}

bool UIElement::doesReceiveEvents()
{
	return this->receiveEvents;
}