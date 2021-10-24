#pragma once
#include <string>
#include "GameManager.h"

class SoundLauncher
{
private:
	std::string path;
	GameManager* gm;

public:
	SoundLauncher(std::string path, GameManager* gm);
	void launch();
};