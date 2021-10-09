#pragma once
#include <vector>
#include "UIElement.h"

class GameManager
{
private:
	bool inGame = false;
	std::vector<UIElement*> UIelems;

public:
	bool isInGame();

	void clearUIElements(bool shouldDelete = false);
	void addUIElement(UIElement& elem);
	void remUIElement(UIElement& elem, bool shouldDelete = false);
};