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

public:
	bool isInGame();

	void clearUIElements(bool shouldDelete = false);
	void addUIElement(UIElement& elem);
	void remUIElement(UIElement& elem, bool shouldDelete = false);

	SoundInfo getSoundInfo();
};