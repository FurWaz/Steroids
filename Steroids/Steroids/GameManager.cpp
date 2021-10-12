#include "GameManager.h"

bool GameManager::isInGame()
{
	return this->inGame;
}

void GameManager::clearUIElements(bool shouldDelete)
{
	for (int i = 0; i < this->UIelems.size(); i++)
	{
		UIElement* el = this->UIelems[i];
		this->UIelems.erase(this->UIelems.begin()+i);
		if (shouldDelete) delete el;
	}
}

void GameManager::addUIElement(UIElement& elem)
{
	this->UIelems.push_back(&elem);
}

void GameManager::remUIElement(UIElement& elem, bool shouldDelete)
{
	for (int i = 0; i < this->UIelems.size(); i++)
	{
		UIElement* el = this->UIelems[i];
		if (el == &elem)
		{
			this->UIelems.erase(this->UIelems.begin() + i);
			if (shouldDelete) delete el;
			break;
		}
	}
}

SoundInfo GameManager::getSoundInfo()
{
	return this->soundInfos;
}