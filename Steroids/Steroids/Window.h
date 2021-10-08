#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <chrono>

class Window
{
private:
	sf::RenderWindow win;
	std::chrono::steady_clock::time_point lastTime;
	float dt;
	float enemyTimeout;
	float shakeAmount;
	Player* player;
	sf::Shader shader;
	sf::RenderTexture renderTex;
	std::vector<Enemy*> enemies;

	sf::Font font;

	int score;

	bool keys[4] = { false, false, false, false };
	void init();
	void addRandomEnemy();
	void shake();

public:
	Window();
	Window(sf::Vector2u size, std::string name);

	void setSize(sf::Vector2u size);
	void setName(std::string name);

	bool isOpen();
	void close();
	void render();
	void getEvents();
	void registerKey(int code, bool state);
	void kickPlayer();
};