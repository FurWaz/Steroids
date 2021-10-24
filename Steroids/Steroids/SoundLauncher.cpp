#include "SoundLauncher.h"

SoundLauncher::SoundLauncher(std::string path, GameManager* gm)
{
	this->path = path;
	this->gm = gm;
}

void SoundLauncher::launch()
{
	this->gm->getSoundBoard()->playMusic(this->path);
	this->gm->clearUIElements();
	this->gm->spawnPlayer();
}