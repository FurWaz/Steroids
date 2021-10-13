#pragma once
#include <vector>
#include "UIElement.h"
#include "soundInfo.h"

class GameManager
{
private:
	bool inGame = false;
	std::vector<UIElement*> UIelems;
	SoundInfo soundInfos;
	sf::Vector2u screenSize;

public:
	bool isInGame();

	void clearUIElements(bool shouldDelete = false);
	void addUIElement(UIElement& elem);
	void remUIElement(UIElement& elem, bool shouldDelete = false);

	SoundInfo getSoundInfo();
	sf::Vector2u getScreenSize();
	void setScreenSize(sf::Vector2u size);
};