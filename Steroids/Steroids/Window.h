#pragma once
#include <SFML/Graphics.hpp>
#include <chrono>
#include "Player.h"
#include "Enemy.h"
#include "ParticleManager.h"
#include "SoundBoard.h"
#include "GameManager.h"

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
	float kickTimeout;
	float lastFPS = 60;
	sf::Shader shader;
	sf::RenderTexture renderTex;
	sf::RenderTexture UITex;
	std::vector<Enemy*> enemies;
	GameManager gm;
	ParticleManager* pMan;

	sf::Font font;
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

	~Window();
};