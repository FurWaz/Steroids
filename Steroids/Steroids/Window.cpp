#include "Window.h"

Window::Window()
{
	this->init();
}

Window::Window(sf::Vector2u size, std::string name)
{
	this->init();
	if (size.x != 0 && size.y != 0) this->setSize(size);
	this->setName(name);
}

void Window::init()
{
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;
	sf::VideoMode mode = sf::VideoMode::getFullscreenModes().at(0);
	this->win.create(mode, "Window", sf::Style::Fullscreen);
	this->win.setVerticalSyncEnabled(true);
	this->renderTex.create(this->win.getSize().x, this->win.getSize().y);
	this->player = new Player(
		sf::Vector2f(this->win.getSize().x/2, this->win.getSize().y/2),
		550.f, 0.f, 50.f
	);
	this->enemyTimeout = 0;
	this->shakeAmount = 0;
	this->score = 0;
	this->shootTimeout = 0;

	if (!this->shader.loadFromFile("./Glare.glsl", sf::Shader::Fragment))
	{
		std::cout << "Error: failed to load shader" << std::endl;
		sf::Shader::bind(&this->shader);
	}

	if (!font.loadFromFile("upheavtt.ttf"))
		std::cout << "Error: failed to load font" << std::endl;
}

void Window::addRandomEnemy()
{
	if (this->enemies.size() > 200) return;
	sf::Vector2f pos(
		std::rand() % this->win.getSize().x,
		std::rand() % this->win.getSize().y
	);
	this->enemies.push_back(new Enemy(pos, 300.f, 0.f, 30.f));
}

void Window::setSize(sf::Vector2u size)
{
	this->win.setSize(size);
	this->renderTex.create(this->win.getSize().x, this->win.getSize().y);
}

void Window::setName(std::string name)
{
	this->win.setTitle(name);
}

bool Window::isOpen()
{
	return this->win.isOpen();
}

void Window::close()
{
	this->win.close();
}

void Window::update()
{
	std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
	this->dt = std::chrono::duration_cast<std::chrono::microseconds>(newTime - lastTime).count() / 1000000.f;
	this->lastTime = newTime;
	if (this->dt > 1000) this->dt = 1;

	this->enemyTimeout += this->dt;
	if (this->enemyTimeout > 1)
	{
		this->enemyTimeout = 0;
		addRandomEnemy();
	}

	this->shootTimeout += this->dt;
	if (this->shootTimeout > 0.2f && this->shootPressed)
	{
		this->shootTimeout = 0;
		this->player->shoot();
	}

	for (int i = 0; i < this->player->bullets.size(); i++)
	{
		Bullet* b = this->player->bullets[i];
		b->update(this->dt);
		sf::Vector2f pos = b->getPos();
		if (pos.x < 0 || pos.x > this->win.getSize().x || pos.y < 0 || pos.y > this->win.getSize().y)
		{
			this->player->bullets.erase(this->player->bullets.begin() + i);
			delete b;
		}
	}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* en = this->enemies.at(i);
		en->setPlayerPos(this->player->getPos());
		en->update(this->dt);
		if (this->player->collides(en))
			this->kickPlayer();
		for (int j = 0; j < this->player->bullets.size(); j++)
		{
			Bullet* b = this->player->bullets.at(j);
			if (b->collides(en))
			{
				this->enemies.erase(this->enemies.begin() + i);
				this->player->bullets.erase(this->player->bullets.begin() + j);
				this->shake();
				delete en;
				delete b;
				score++;
				continue;
			}
		}
	}
	this->player->update(this->dt);
}

void Window::render()
{
	sf::RenderStates rs;
	rs.shader = &this->shader;
	this->win.clear(sf::Color::Black);
	this->renderTex.clear(sf::Color::Black);

	for (int i = 0; i < this->player->bullets.size(); i++)
		this->renderTex.draw(this->player->bullets[i]->draw(this->dt));
	for (int i =0; i < this->enemies.size(); i++)
		this->renderTex.draw(this->enemies[i]->draw(this->dt));
	this->renderTex.draw(this->player->draw(this->dt));
	this->renderTex.display();

	// UI stuff (text and life bars)
	sf::Text scoreText(
		"score: "+std::to_string(this->score),
		this->font, 30
	);
	scoreText.setPosition(sf::Vector2f(10, 10));
	/*
	this->lastFPS += ((1.f / this->dt) - this->lastFPS) * 0.02;
	sf::Text fpsText(
		"FPS: " + std::to_string((int)this->lastFPS),
		this->font, 30
	);
	fpsText.setPosition(sf::Vector2f(200, 10));
	*/

	sf::RectangleShape playerLife;
	playerLife.setSize(sf::Vector2f(60, 4));
	playerLife.setOrigin(sf::Vector2f(30, 2));
	playerLife.setOutlineColor(sf::Color::White);
	playerLife.setFillColor(sf::Color::Transparent);
	playerLife.setOutlineThickness(2);
	playerLife.setPosition(
		this->player->getPos().x,
		this->player->getPos().y - this->player->getSize()
	);
	sf::RectangleShape playerBar;
	playerBar.setOrigin(sf::Vector2f(0, 2));
	playerBar.setFillColor(sf::Color::White);
	playerBar.setSize(sf::Vector2f(this->player->getLife()*60/this->player->getMaxLife(), 4));
	playerBar.setPosition(
		this->player->getPos().x-30,
		this->player->getPos().y - this->player->getSize()
	);
	this->renderTex.draw(scoreText);
	this->renderTex.draw(playerLife);
	this->renderTex.draw(playerBar);

	// camera movements (shake and zoom)
	sf::Sprite sprite(this->renderTex.getTexture());
	sprite.setOrigin(sf::Vector2f(
		this->win.getSize().x * 0.5f,
		this->win.getSize().y * 0.5f
	));
	sprite.setPosition(sf::Vector2f(
		this->win.getSize().x * 0.5f,
		this->win.getSize().y * 0.5f
	));
	if (this->shakeAmount > 1)
	{
		this->shakeAmount--;
		sprite.setPosition(
			this->win.getSize().x * 0.5f + std::rand() % (int)(this->shakeAmount) - this->shakeAmount * 0.5f,
			this->win.getSize().y * 0.5f + std::rand() % (int)(this->shakeAmount) - this->shakeAmount * 0.5f
		);
	}
	sprite.setScale(sf::Vector2f(
		1.f + this->shakeAmount * 0.001f,
		1.f + this->shakeAmount * 0.001f
	));

	this->shader.setUniform("multiply", this->shakeAmount * 0.03f + 1.1f);
	this->win.draw(sprite, rs);
	//this->win.draw(fpsText);
	this->win.display();
}

void Window::shake()
{
	this->shakeAmount = 25;
}

void Window::getEvents()
{
	sf::Event ev;
	while (this->win.pollEvent(ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->close();
			break;
		case sf::Event::MouseMoved:
			this->player->setMousePos(sf::Mouse::getPosition(this->win));
			break;
		case sf::Event::KeyPressed:
			this->registerKey(ev.key.code, true);
			break;
		case sf::Event::KeyReleased:
			this->registerKey(ev.key.code, false);
			break;
		case sf::Event::MouseButtonPressed:
			this->shootPressed = true;
			break;
		case sf::Event::MouseButtonReleased:
			this->shootPressed = false;
			break;
		default:
			break;
		}
	}
}

void Window::registerKey(int code, bool state)
{
	switch (code)
	{
	case sf::Keyboard::Up:
	case sf::Keyboard::Z:
	case sf::Keyboard::W:
		this->keys[0] = state;
		break;
	case sf::Keyboard::Down:
	case sf::Keyboard::S:
		this->keys[1] = state;
		break;
	case sf::Keyboard::Right:
	case sf::Keyboard::D:
		this->keys[2] = state;
		break;
	case sf::Keyboard::Left:
	case sf::Keyboard::A:
	case sf::Keyboard::Q:
		this->keys[3] = state;
		break;
	default:
		break;
	}
	this->player->setKeys(this->keys);
}

void Window::kickPlayer()
{
	this->player->setLife(this->player->getLife()-1);
	if (this->player->getLife() == 0)
		this->win.close();
}