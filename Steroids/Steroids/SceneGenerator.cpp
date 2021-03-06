#include "SceneGenerator.h"
#include "Button.h"
#include "Files.h"
#include "UIList.h"
#include "SoundLauncher.h"
#include <shobjidl.h>
#include <iostream>

void quitCallback()
{
	std::exit(0);
}

GameManager* gm;

void SceneGenerator::setGameManager(GameManager& gameManager)
{
	gm = &gameManager;
}

void SceneGenerator::generateMenuScene()
{
	gm->clearUIElements();
	Button* b = new Button (
		sf::Vector2i(gm->getScreenSize().x/2, gm->getScreenSize().y/2+100),
		sf::Vector2i(200, 80),
		"Quit"
	);
	b->setCallback(quitCallback);
	gm->addUIElement(*b);
	b = new Button(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y / 2),
		sf::Vector2i(200, 80),
		"Play"
	);
	b->setCallback(SceneGenerator::generateFileExplorerScene);
	gm->addUIElement(*b);

	Text* t = new Text(
		sf::Vector2i(gm->getScreenSize().x/2, 70),
		sf::Vector2i(gm->getScreenSize().x, 140),
		"Steroids", 120
	);
	gm->addUIElement(*t);
}

void SceneGenerator::generateDeadScene()
{
	gm->clearUIElements();
	Button* b = new Button(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.75),
		sf::Vector2i(200, 80),
		"Menu"
	);
	b->setCallback(SceneGenerator::generateMenuScene);
	gm->addUIElement(*b);

	Text* t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.3),
		sf::Vector2i(gm->getScreenSize().x, 140),
		"You're dead", 120
	);
	gm->addUIElement(*t);
	t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.3 + 70),
		sf::Vector2i(gm->getScreenSize().x, 40),
		"Score: "+std::to_string(gm->score), 30
	);
	gm->addUIElement(*t);
	gm->getSoundInfo()->stopSound();
	gm->player = nullptr;
}

void SceneGenerator::generateFileExplorerScene()
{
	Files f;
	f.setStartFolder(f.getHomeDirectory() + "\\Music");

	gm->clearUIElements();
	Text* t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, 30),
		sf::Vector2i(400, 60),
		"Choose a song", 50
	);
	gm->addUIElement(*t);
	t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, 70),
		sf::Vector2i(gm->getScreenSize().x, 30),
		"Put your .wav songs in "+f.getStartFolder(), 20
	);
	gm->addUIElement(*t);

	Button* b = new Button(
		sf::Vector2i(75, 25),
		sf::Vector2i(140, 40),
		"Back"
	);
	b->setCallback(SceneGenerator::generateMenuScene);
	gm->addUIElement(*b);

	UIList* list = new UIList(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y / 2),
		sf::Vector2i(gm->getScreenSize().x-20, gm->getScreenSize().y-180)
	);

	std::vector<std::string> musics = f.getFiles();
	for (unsigned int i = 0; i < musics.size(); i++)
	{
		Button* b = new Button(
			sf::Vector2i(0, 10),
			sf::Vector2i(gm->getScreenSize().x*0.4, 60),
			Files::getFileName(musics[i])
		);
		SoundLauncher* sl = new SoundLauncher(musics[i], gm);
		b->setCallback(&SoundLauncher::launch, sl);
		list->addElement(b);
	}

	gm->addUIElement(*list);
}

void SceneGenerator::generateWinScene()
{
	gm->clearUIElements();
	Button* b = new Button(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.75),
		sf::Vector2i(200, 80),
		"Menu"
	);
	b->setCallback(SceneGenerator::generateMenuScene);
	gm->addUIElement(*b);

	Text* t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.3),
		sf::Vector2i(gm->getScreenSize().x, 140),
		"You made it !", 120
	);
	gm->addUIElement(*t);
	t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.3 + 70),
		sf::Vector2i(gm->getScreenSize().x, 40),
		"Score: " + std::to_string(gm->score), 30
	);
	gm->addUIElement(*t);
	t = new Text(
		sf::Vector2i(gm->getScreenSize().x / 2, gm->getScreenSize().y * 0.3 + 100),
		sf::Vector2i(gm->getScreenSize().x, 40),
		"Life: " + std::to_string(gm->player->getLife() * 100 / gm->player->getMaxLife()) + "%", 30
	);
	gm->addUIElement(*t);
	gm->player = nullptr;
}