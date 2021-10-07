#include "Window.h"

Window::Window()
{
	this->init();
}

Window::Window(sf::Vector2u size, std::string name)
{
	this->init();
	this->setSize(size);
	this->setName(name);
}

void Window::init()
{
	this->win.create(sf::VideoMode(1280, 720), "Window");
	this->renderTex.create(1280, 720);
	this->win.setVerticalSyncEnabled(true);
	this->player = new Player(sf::Vector2f(640, 360), 500.f, 0.f, 50.f);
	this->enemyTimeout = 0;
	this->shakeAmount = 0;

	if (this->shader.loadFromFile("./Glare.glsl", sf::Shader::Fragment))
	{
		std::cout << "binding glare shader" << std::endl;
		sf::Shader::bind(&this->shader);
	}
}

void Window::addRandomEnemy()
{
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

void Window::render()
{
	std::chrono::steady_clock::time_point newTime = std::chrono::steady_clock::now();
	this->dt = std::chrono::duration_cast<std::chrono::microseconds>(newTime-lastTime).count() / 1000000.f;
	this->lastTime = newTime;
	if (this->dt > 1000) this->dt = 0;

	this->enemyTimeout += this->dt;
	if (this->enemyTimeout > 1)
	{
		this->enemyTimeout = 0;
		addRandomEnemy();
	}

	sf::RenderStates rs;
	rs.shader = &this->shader;

	// render
	this->renderTex.clear(sf::Color::Black);
	for (int i = 0; i < this->player->bullets.size(); i++)
	{
		Bullet* b = this->player->bullets[i];
		b->update(this->dt);
		this->renderTex.draw(b->draw(this->dt));
		sf::Vector2f pos = b->getPos();
		if (pos.x < 0 || pos.x > this->win.getSize().x || pos.y < 0 || pos.y > this->win.getSize().y)
		{
			this->player->bullets.erase(this->player->bullets.begin()+i);
			delete b;
		}
	}
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* en = this->enemies.at(i);
		en->setPlayerPos(this->player->getPos());
		en->update(this->dt);
		if (this->player->collides(en));
			//this->win.close();
		this->renderTex.draw(en->draw(this->dt));
		for (int j = 0; j < this->player->bullets.size(); j++)
		{
			if (this->player->bullets.at(j)->collides(en))
			{
				this->enemies.erase(this->enemies.begin() + i);
				this->shake();
				delete en;
				continue;
			}
		}
	}
	this->player->update(this->dt);
	this->renderTex.draw(this->player->draw(this->dt));
	this->renderTex.display();

	sf::Sprite sprite(this->renderTex.getTexture());
	if (this->shakeAmount > 1)
	{
		this->shakeAmount--;
		sprite.setPosition(
			std::rand() % (int)this->shakeAmount,
			std::rand() % (int)this->shakeAmount
		);
	}

	this->win.draw(sprite, rs);
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
			this->player->shoot();
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