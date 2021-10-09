#pragma once
#include "GameManager.h"

class SceneGenerator
{
public:
	static void generateMenuScene(GameManager &gm);
	static void generateInGameScene(GameManager& gm);
	static void generateFileExplorerScene(GameManager& gm);
};