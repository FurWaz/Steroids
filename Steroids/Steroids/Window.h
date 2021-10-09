#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Player.h"
#include "Enemy.h"
#include "ParticleManager.h"
#include "SoundBoard.h"

class Window
{
private:
	sf::RenderWindow win;
	std::string title;
	sf::Vector2u size;
	bool isFullscreen;
	std::chrono::steady_clock::time_point lastTime;
	float dt;
	float enemyTimeout;
	float shootTimeout;
	float shakeAmount;
	float lastFPS = 60;
	Player* player = nullptr;
	sf::Shader shader;
	sf::RenderTexture renderTex;
	sf::RenderTexture UITex;
	std::vector<Enemy*> enemies;
	ParticleManager pMan;
	SoundBoard soundBoard;

	sf::Font font;
	int score;
	bool keys[4] = { false, false, false, false };
	bool shootPressed = false;
	void init(sf::Vector2u size, std::string name);
	void addRandomEnemy();
	void shake();
	void toogleFullscreen();

public:
	Window();
	Window(sf::Vector2u size, std::string name);

	void setSize(sf::Vector2u size);
	void setName(std::string name);

	bool isOpen();
	void close();
	void update();
	void render();
	void getEvents();
	void registerKey(int code, bool state);
	void kickPlayer();
};