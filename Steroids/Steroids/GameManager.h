#pragma once
#include <vector>
#include "UIElement.h"
#include "soundInfo.h"
#include "Player.h"
#include "SoundBoard.h"

class GameManager
{
private:
	bool inGame = false;
	sf::Vector2i mousePos;
	std::vector<UIElement*> UIelems;
	SoundInfo soundInfos;
	sf::Vector2u screenSize;
	SoundBoard sb;
	void hoverElement();
	void pressElement(bool state);
	void scrollElement(float amount);

public:
	Player* player = nullptr;
	bool isInGame();

	void clearUIElements();
	void addUIElement(UIElement& elem);
	void remUIElement(UIElement& elem);
	void processEvent(sf::Event ev);
	std::vector<UIElement*> getUIElements();
	SoundBoard* getSoundBoard();

	void setMousePos(sf::Vector2i pos);
	SoundInfo getSoundInfo();
	sf::Vector2u getScreenSize();
	void setScreenSize(sf::Vector2u size);
	void spawnPlayer();
};