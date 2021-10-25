#include "GameManager.h"

bool GameManager::isInGame()
{
	return this->inGame;
}

void GameManager::clearUIElements()
{
	this->UIelems.clear();
	this->shakeAmount = 20;
	this->sb.playCrush();
}

void GameManager::addUIElement(UIElement& elem)
{
	this->UIelems.push_back(&elem);
}

void GameManager::remUIElement(UIElement& elem)
{
	for (int i = 0; i < this->UIelems.size(); i++)
	{
		UIElement* el = this->UIelems[i];
		if (el == &elem)
		{
			this->UIelems.erase(this->UIelems.begin() + i);
			break;
		}
	}
}

void GameManager::processEvent(sf::Event ev)
{
	switch (ev.type)
	{
	case sf::Event::MouseMoved:
		this->hoverElement();
		break;
	case sf::Event::MouseButtonPressed:
		this->pressElement(true);
		break;
	case sf::Event::MouseWheelScrolled:
		this->scrollElement(ev.mouseWheelScroll.delta);
		break;
	case sf::Event::MouseButtonReleased:
		this->pressElement(false);
		break;
	default:
		break;
	}
}

std::vector<UIElement*> GameManager::getUIElements()
{
	return this->UIelems;
}

SoundInfo* GameManager::getSoundInfo()
{
	return &this->soundInfos;
}

sf::Vector2u GameManager::getScreenSize()
{
	return this->screenSize;
}

void GameManager::setScreenSize(sf::Vector2u size)
{
	this->screenSize = size;
}

void GameManager::hoverElement()
{
	for (int i = 0; i < this->UIelems.size(); i++)
	{
		UIElement* el = this->UIelems[i];
		if (el->collides(this->mousePos))
		{
			if (!el->isHovered())
			{
				if (el->doesReceiveEvents())
					this->sb.playSelect();
				el->onHover(true);
			}
		} else
		{
			if (el->isHovered())
				el->onHover(false);
		}
		std::vector<UIElement*> elems = el->getElements();
		for (unsigned int j = 0; j < elems.size(); j++)
		{
			UIElement* el2 = elems[j];
			sf::Vector2f pos = el->getPos() + el2->getPos();
			sf::Vector2f size = el2->getSize();
			if (
				this->mousePos.x >= pos.x - size.x / 2 &&
				this->mousePos.x < pos.x + size.x / 2 &&
				this->mousePos.y >= pos.y - size.y / 2 &&
				this->mousePos.y < pos.y + size.y / 2
				)
			{
				if (!el2->isHovered())
				{
					if (el2->doesReceiveEvents())
						this->sb.playSelect();
					el2->onHover(true);
				}
			}
			else
			{
				if (el2->isHovered())
					el2->onHover(false);
			}
		}
	}
}

void GameManager::pressElement(bool state)
{
	for (int i = 0; i < this->UIelems.size(); i++)
	{
		UIElement* el = this->UIelems[i];
		if (el->collides(this->mousePos))
		{
			if (el->isClicked() != state)
			{
				el->onClick(state);
				if (state && el->doesReceiveEvents())
					this->sb.playClick();
			}
		}
		else
		{
			if (el->isClicked())
				el->onClick(false);
		}
		std::vector<UIElement*> elems = el->getElements();
		for (unsigned int j = 0; j < elems.size(); j++)
		{
			UIElement* el2 = elems[j];
			sf::Vector2f pos = el->getPos() + el2->getPos();
			sf::Vector2f size = el2->getSize();
			if (
				this->mousePos.x >= pos.x - size.x / 2 &&
				this->mousePos.x < pos.x + size.x / 2 &&
				this->mousePos.y >= pos.y - size.y / 2 &&
				this->mousePos.y < pos.y + size.y / 2
				)
			{
				if (el2->isClicked() != state)
				{
					el2->onClick(state);
					if (state && el2->doesReceiveEvents())
						this->sb.playClick();
				}
			}
			else
			{
				if (el2->isClicked())
					el2->onClick(false);
			}
		}
	}
}

void GameManager::scrollElement(float amount)
{
	for (int i = 0; i < this->UIelems.size(); i++)
	{
		UIElement* el = this->UIelems[i];
		if (el->collides(this->mousePos))
			el->onScroll(amount);
	}
}

void GameManager::setMousePos(sf::Vector2i pos)
{
	this->mousePos = pos;
}

SoundBoard* GameManager::getSoundBoard()
{
	return &this->sb;
}

void GameManager::spawnPlayer()
{
	this->player = new Player(
		sf::Vector2f(this->screenSize.x, this->screenSize.y) * 0.5f,
		500.f, 0.f, 50.f
	);
	this->inGame = true;
}

void GameManager::update(float dt)
{
	this->soundInfos.update(dt);
}