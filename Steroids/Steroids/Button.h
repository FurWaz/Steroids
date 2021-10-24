#pragma once
#include "UIElement.h"
#include "CallbackContainer.h"
#include "Text.h"

class Button : virtual public UIElement
{
private:
	CallbackContainer* cont = nullptr;
	sf::Color color;
	sf::RectangleShape rect;
	Text* text;

public:
	Button(sf::Vector2i pos, sf::Vector2i size, std::string text);
	sf::Sprite draw(float dt);
	void onHover(bool state);
	void onClick(bool state);

	template<class T> void setCallback(void (T::* callback)(), T* c)
	{
		this->cont = new TypedCallbackContainer<T>(callback, c);
	}

	void setCallback(void (*callback)())
	{
		this->cont = new VoidCallbackContainer(callback);
	}
};