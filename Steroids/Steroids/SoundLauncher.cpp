#include "SoundLauncher.h"
#include "SceneGenerator.h"

SoundLauncher::SoundLauncher(std::string path, GameManager* gm)
{
	this->path = path;
	this->gm = gm;
}

void SoundLauncher::launch()
{
	this->gm->getSoundBoard()->playMusic(this->path);
	this->gm->getSoundInfo()->setSoundBuffer(
		this->gm->getSoundBoard()->getMusicBuffer()
	);
	this->gm->getSoundInfo()->setCallback(SceneGenerator::generateWinScene);
	this->gm->clearUIElements();
	this->gm->spawnPlayer();
}