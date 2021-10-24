#pragma once
#include "UIElement.h"
class Text : virtual public UIElement
{
public:
	std::string string;
	sf::Text text;
	sf::Font font;

public:
	Text(sf::Vector2i pos, sf::Vector2i size, std::string text, int charSize = 30);
	void setColor(sf::Color color);
	sf::Sprite draw(float dt);
	std::string getString();
};