#include "UIElement.h"

UIElement::UIElement()
{
	this->setDimensions(sf::FloatRect(0, 0, 100, 100));
}

UIElement::UIElement(sf::FloatRect dims)
{
	this->setDimensions(dims);
}

UIElement::~UIElement()
{

}

void UIElement::resizeTextures()
{
	this->renderTex.create(this->dims.width, this->dims.height);
	this->sprite.setTexture(this->renderTex.getTexture());
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
	void resizeTextures();
}

void UIElement::setDimensions(sf::FloatRect dims)
{
	this->dims = dims;
	void resizeTextures();
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

void UIElement::update(float dt)
{

}

void UIElement::onHover(bool state)
{
	this->hovered = state;
}

void UIElement::onClick(bool state)
{
	this->clicked = state;
}

sf::Sprite UIElement::draw(float dt)
{
	this->renderTex.clear(sf::Color::Black);
	return this->sprite;
}