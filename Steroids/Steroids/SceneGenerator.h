#pragma once
#include "GameManager.h"

class SceneGenerator
{
public:
	static void setGameManager(GameManager& gameManager);
	static void generateMenuScene();
	static void generateDeadScene();
	static void generateFileExplorerScene();
	static void generateWinScene();
};