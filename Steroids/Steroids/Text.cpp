#include "Text.h"

Text::Text(sf::Vector2i pos, sf::Vector2i size, std::string text, int charSize):
	UIElement(sf::FloatRect(pos.x, pos.y, size.x, size.y))
{
	this->font.loadFromFile("./upheavtt.ttf");
	this->string = text;
	this->text = sf::Text(this->string, this->font, charSize);
	this->text.setOrigin(this->text.getLocalBounds().width / 2, this->text.getLocalBounds().height*1.4);
	this->text.setPosition(this->dims.width / 2, this->dims.height / 2);
	this->renderTex.clear(sf::Color::Transparent);
	this->renderTex.draw(this->text);
	this->renderTex.display();
	this->receiveEvents = false;
}

void Text::setColor(sf::Color color)
{
	this->text.setFillColor(color);
	this->renderTex.clear(sf::Color::Transparent);
	this->renderTex.draw(this->text);
	this->renderTex.display();
}

sf::Sprite Text::draw(float dt)
{
	return this->sprite;
}

std::string Text::getString()
{
	return this->string;
}