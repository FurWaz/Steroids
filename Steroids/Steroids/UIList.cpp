#include "UIList.h"
#include <iostream>

UIList::UIList(sf::Vector2i pos, sf::Vector2i size) :
	UIElement(sf::FloatRect(pos.x, pos.y, size.x, size.y))
{
	this->scrollAmount = 40;
	this->onScroll(0);
	this->receiveEvents = false;
}

void UIList::addElement(UIElement* elem)
{
	unsigned int shift = 0;
	if (this->elements.size() > 0)
	{
		UIElement* el = this->elements[this->elements.size() - 1];
		shift = el->getSize().y + el->getPos().y;
	}
	elem->setPos(elem->getPos() + sf::Vector2f(0, shift));
	this->elements.push_back(elem);
	this->onScroll(0);
}

void UIList::remElement(int index)
{
	this->elements.erase(this->elements.begin() + index);
	this->onScroll(0);
}

void UIList::onScroll(float amount)
{
	this->scrollAmount += amount * 10;
	for (unsigned int i = 0; i < this->elements.size(); i++)
	{
		this->elements[i]->setPos(this->elements[i]->getPos() + sf::Vector2f(0, amount));
	}
}

std::vector<UIElement*> UIList::getElements()
{
	return this->elements;
}

sf::Sprite UIList::draw(float dt)
{
	this->renderTex.clear(sf::Color::Transparent);
	for (unsigned int i = 0; i < this->elements.size(); i++)
	{
		UIElement* el = this->elements[i];
		sf::Sprite spr = el->draw(0);
		spr.setPosition(spr.getPosition() + sf::Vector2f(this->dims.width / 2, this->dims.height / 2));
		this->renderTex.draw(spr);
	}
	this->renderTex.display();
	return this->sprite;
}