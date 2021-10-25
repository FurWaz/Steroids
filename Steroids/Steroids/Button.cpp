#include "Button.h"
#include <iostream>

Button::Button(sf::Vector2i pos, sf::Vector2i size, std::string text):
    UIElement(sf::FloatRect(pos.x, pos.y, size.x, size.y))
{
    this->color = sf::Color::Red;
    this->text = new Text(sf::Vector2i(size.x/2, size.y/2), size, text);
    rect.setPosition(2, 2);
    rect.setSize(sf::Vector2f(this->dims.width - 4, this->dims.height - 4));
    rect.setOutlineThickness(2);
    rect.setFillColor(sf::Color::Black);
    this->onHover(false);
    this->renderTex.clear(sf::Color::Black);
    this->renderTex.draw(rect);
    this->renderTex.draw(this->text->draw(0));
    this->renderTex.display();
}

void Button::onHover(bool state)
{
    this->hovered = state;
    this->color = state ? sf::Color::Red : sf::Color::Blue;
    this->rect.setOutlineColor(this->color);
    this->text->setColor(this->color);
    this->renderTex.clear(sf::Color::Black);
    this->renderTex.draw(rect);
    this->renderTex.draw(this->text->draw(0));
    this->renderTex.display();
}

void Button::onClick(bool state)
{
    this->clicked = state;
    if (this->cont != nullptr && !state)
        this->cont->func();
}

sf::Sprite Button::draw(float dt)
{
    return this->sprite;
}