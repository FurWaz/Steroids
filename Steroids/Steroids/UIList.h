#pragma once
#include "UIElement.h"

class UIList : public UIElement
{
private:
	std::vector<UIElement*> elements;
	float scrollAmount;

public:
	UIList(sf::Vector2i pos, sf::Vector2i size);
	void addElement(UIElement* elem);
	void remElement(int index);

	void onScroll(float amount);
	std::vector<UIElement*> getElements();
	sf::Sprite draw(float dt);
};