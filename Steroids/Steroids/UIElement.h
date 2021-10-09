#pragma once
#include <SFML/Graphics.hpp>

class UIElement
{
private:
	sf::Sprite sprite;
	sf::RenderTexture renderTex;
	sf::FloatRect dims;
	bool hovered = false;
	bool clicked = false;

	void resizeTextures();

public:
	UIElement();
	UIElement(sf::FloatRect dims);
	~UIElement();

	void setPos(sf::Vector2f pos);
	void setSize(sf::Vector2f size);
	void setDimensions(sf::FloatRect dims);
	sf::Vector2f getPos();
	sf::Vector2f getSize();
	sf::FloatRect getDimensions();
	bool isHovered();
	bool isClicked();
	bool collides(UIElement& other);

	virtual void onHover(bool state);
	virtual void onClick(bool state);
	virtual void update(float dt);
	virtual sf::Sprite draw(float dt);
};