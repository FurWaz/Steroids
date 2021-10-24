#pragma once
#include <SFML/Graphics.hpp>

class UIElement
{
protected:
	sf::Sprite sprite;
	sf::RenderTexture renderTex;
	sf::FloatRect dims;
	bool hovered = false;
	bool clicked = false;
	bool receiveEvents = true;

	float moveX = 0, moveY = 0, rot = 0;
	float moveX_s = 0, moveY_s = 0, rot_s = 0;

	void init();
	void resizeTextures();

public:
	UIElement();
	UIElement(sf::FloatRect dims);

	void setPos(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setDimensions(sf::FloatRect dims);
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	sf::FloatRect getDimensions();
	bool isHovered();
	bool isClicked();
	bool collides(UIElement& other);
	bool collides(sf::Vector2i pos);
	bool doesReceiveEvents();

	virtual void onHover(bool state);
	virtual void onScroll(float amount);
	virtual void onClick(bool state);
	virtual void update(float dt);
	virtual std::vector<UIElement*> getElements();
	virtual sf::Sprite draw(float dt);
};