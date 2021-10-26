#include "Window.h"
#include "SceneGenerator.h"
#include "Text.h"

Window::Window()
{
	this->init(sf::Vector2u(), "Steroids");
}

Window::Window(sf::Vector2u size, std::string name)
{
	this->init(size, name);
}

void Window::init(sf::Vector2u size, std::string name)
{
	this->setSize(size);
	this->setName(name);
	sf::ContextSettings cs;
	cs.antialiasingLevel = 8;
	this->win.setVerticalSyncEnabled(true);
	this->win.setFramerateLimit(60);
	this->enemyTimeout = 0;
	this->gm.shakeAmount = 0;
	this->gm.score = 0;
	this->shootTimeout = 0;
	this->pMan = new ParticleManager(this->gm);

	if (!this->shader.loadFromFile("./Glare.glsl", sf::Shader::Fragment))
	{
		std::cout << "Error: failed to load shader" << std::endl;
		sf::Shader::bind(&this->shader);
	}

	if (!font.loadFromFile("upheavtt.ttf"))
		std::cout << "Error: failed to load font" << std::endl;

	SceneGenerator::setGameManager(this->gm);
	SceneGenerator::generateMenuScene();
}

void Window::addRandomEnemy()
{
	if (this->enemies.size() > 200) return;
	sf::Vector2f pos;
	if (std::rand() % 2)
		pos = sf::Vector2f(
			std::rand() % this->win.getSize().x,
			std::rand() % 2 ? 0 : this->win.getSize().y
		);
	else 
		pos = sf::Vector2f(
			std::rand() % 2 ? 0 : this->win.getSize().x,
			std::rand() % this->win.getSize().y
		);
	this->enemies.push_back(new Enemy(pos, 300.f, 0.f, 30.f));
}

void Window::setSize(sf::Vector2u size)
{
	sf::VideoMode fullMode = sf::VideoMode::getFullscreenModes()[0];
	bool shouldFullscreen = (fullMode.width == size.x && fullMode.height == size.y) || (size.x == 0 || size.y == 0);
	this->isFullscreen = shouldFullscreen;
	if (shouldFullscreen) size = sf::Vector2u(fullMode.width, fullMode.height);
	else this->size = size;
	this->win.create(sf::VideoMode(size.x, size.y), this->title, shouldFullscreen? sf::Style::Fullscreen: sf::Style::Close);
	this->renderTex.create(size.x, size.y);
	this->UITex.create(size.x, size.y);
	this->gm.setScreenSize(size);
}

void Window::setName(std::string name)
{
	this->title = name;
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

	this->pMan->update(this->dt);
	this->gm.update(dt);
	this->enemyTimeout += this->dt;
	this->shootTimeout += this->dt;
	this->kickTimeout += this->dt;

	// update the UI
	std::vector<UIElement*> elems = gm.getUIElements();
	for (unsigned int i = 0; i < elems.size(); i++)
		elems[i]->update(this->dt);

	// ingame-related updates (don't do them if there is no player)
	if (this->gm.player == nullptr) return;
	if (this->enemyTimeout > (0.6f - this->gm.getSoundInfo()->getBassLevel()*0.5f))
	{
		this->enemyTimeout = 0;
		addRandomEnemy();
	}
	if (this->shootTimeout > 0.1f && this->shootPressed)
	{
		this->shootTimeout = 0;
		this->gm.getSoundBoard()->playShoot();
		this->gm.player->shoot();
	}

	for (int i = 0; i < this->gm.player->bullets.size(); i++)
	{
		Bullet* b = this->gm.player->bullets[i];
		b->update(this->dt);
		sf::Vector2f pos = b->getPos();
		if (pos.x < 0 || pos.x > this->win.getSize().x || pos.y < 0 || pos.y > this->win.getSize().y)
		{
			delete this->gm.player->bullets[i];
			this->gm.player->bullets.erase(this->gm.player->bullets.begin() + i);
		}
	}
	this->gm.player->setSize(1);
	for (int i = 0; i < this->enemies.size(); i++)
	{
		Enemy* en = this->enemies[i];
		en->setSpeedFactor(this->gm.getSoundInfo()->getBassLevel()*2 + 0.1);
		en->setPlayerPos(this->gm.player->getPos());
		en->update(this->dt);
		if (this->gm.player->collides(en))
		{
			this->kickPlayer();
			if (this->gm.player == nullptr)
				return;
			this->gm.player->setSize(0.8);
		}
		for (int j = 0; j < this->gm.player->bullets.size(); j++)
		{
			Bullet* b = this->gm.player->bullets[j];
			if (b->collides(en))
			{
				this->gm.getSoundBoard()->playCrush();
				this->pMan->addCrushParticles(en->getPos());
				this->shake();
				delete this->enemies[i];
				delete this->gm.player->bullets[j];
				this->enemies.erase(this->enemies.begin() + i);
				this->gm.player->bullets.erase(this->gm.player->bullets.begin() + j);
				this->gm.score++;
				break;
			}
		}
	}
	this->gm.player->update(this->dt);
	if (sf::Joystick::isConnected(0) && false)
	{
		sf::Vector2f movement(
			sf::Joystick::getAxisPosition(0, sf::Joystick::X),
			sf::Joystick::getAxisPosition(0, sf::Joystick::Y)
		);
		this->gm.player->setMovement(movement);
		this->gm.player->setSpeed( (abs(movement.x) + abs(movement.y)) * 0.005 * 1.43);
		if (sf::Joystick::getAxisPosition(0, sf::Joystick::R) != 0)
			this->gm.player->setDirection(std::atan2f(
				-sf::Joystick::getAxisPosition(0, sf::Joystick::Z),
				sf::Joystick::getAxisPosition(0, sf::Joystick::R)
			));
		this->shootPressed = sf::Joystick::isButtonPressed(0, 7);
	}
}

void Window::render()
{
	sf::RenderStates rs;
	rs.shader = &this->shader;
	this->win.clear(sf::Color::Black);
	this->renderTex.clear(sf::Color::Black);
	this->UITex.clear(sf::Color::Transparent);

	// draw the UI
	std::vector<UIElement*> elems = gm.getUIElements();
	for (unsigned int i = 0; i < elems.size(); i++)
		this->UITex.draw(elems[i]->draw(this->dt));

	//draw all particles
	std::vector<Particle*> ps = this->pMan->getParticles();
	for (int i = 0; i < ps.size(); i++)
		this->renderTex.draw(ps[i]->draw(this->dt));
	if (this->gm.player != nullptr)
	{
		BackParticle** bps = this->pMan->getBackParticles();
		for (int i = 0; i < this->pMan->NB_BACKPARTICLES; i++)
			this->renderTex.draw(bps[i]->draw(this->dt));
		for (int i = 0; i < this->enemies.size(); i++)
			this->renderTex.draw(this->enemies[i]->draw(this->dt));
		this->renderTex.draw(this->gm.player->draw(this->dt));
		for (int i = 0; i < this->gm.player->bullets.size(); i++)
			this->renderTex.draw(this->gm.player->bullets[i]->draw(this->dt));
	}
	this->renderTex.display();

	if (this->gm.player != nullptr)
	{
		// UI stuff (text and life bars)
		sf::Text scoreText(
			"score: " + std::to_string(this->gm.score),
			this->font, 30
		);
		scoreText.setPosition(sf::Vector2f(10, 10));
		this->UITex.draw(scoreText);

		sf::RectangleShape playerLife;
		playerLife.setSize(sf::Vector2f(60, 4));
		playerLife.setOrigin(sf::Vector2f(30, 2));
		playerLife.setOutlineColor(sf::Color::White);
		playerLife.setFillColor(sf::Color::Transparent);
		playerLife.setOutlineThickness(2);
		playerLife.setPosition(
			this->gm.player->getPos().x,
			this->gm.player->getPos().y - this->gm.player->getSize()
		);
		sf::RectangleShape playerBar;
		playerBar.setOrigin(sf::Vector2f(0, 2));
		playerBar.setFillColor(sf::Color::White);
		playerBar.setSize(sf::Vector2f(this->gm.player->getLife() * 60 / this->gm.player->getMaxLife(), 4));
		playerBar.setPosition(
			this->gm.player->getPos().x - 30,
			this->gm.player->getPos().y - this->gm.player->getSize()
		);
		this->UITex.draw(playerLife);
		this->UITex.draw(playerBar);
	}
	this->UITex.display();

	// camera movements (shake and zoom)
	sf::Sprite renderSprite(this->renderTex.getTexture());
	sf::Sprite UISprite(this->UITex.getTexture());
	renderSprite.setOrigin(sf::Vector2f(this->win.getSize().x * 0.5f, this->win.getSize().y * 0.5f));
	renderSprite.setPosition(sf::Vector2f(this->win.getSize().x * 0.5f, this->win.getSize().y * 0.5f));
	UISprite.setOrigin(sf::Vector2f(this->win.getSize().x * 0.5f, this->win.getSize().y * 0.5f));
	UISprite.setPosition(sf::Vector2f(this->win.getSize().x * 0.5f, this->win.getSize().y * 0.5f));
	float screenScale = 1.f + this->gm.shakeAmount * 0.001f;
	renderSprite.setScale(sf::Vector2f(screenScale, screenScale));
	UISprite.setScale(sf::Vector2f(screenScale, screenScale));
	if (this->gm.shakeAmount > 1)
	{
		this->gm.shakeAmount--;
		renderSprite.setPosition(
			this->win.getSize().x * 0.5f + std::rand() % (int)(this->gm.shakeAmount) - this->gm.shakeAmount * 0.5f,
			this->win.getSize().y * 0.5f + std::rand() % (int)(this->gm.shakeAmount) - this->gm.shakeAmount * 0.5f
		);
		UISprite.setPosition(
			this->win.getSize().x * 0.5f + std::rand() % (int)(this->gm.shakeAmount) - this->gm.shakeAmount * 0.5f,
			this->win.getSize().y * 0.5f + std::rand() % (int)(this->gm.shakeAmount) - this->gm.shakeAmount * 0.5f
		);
	}

	// apply shader effects and display
	this->shader.setUniform("multiply", this->gm.shakeAmount * 0.05f + 0.9f);
	this->shader.setUniform("texture_inverse", 0.003f);
	this->win.draw(renderSprite, rs);
	this->shader.setUniform("multiply", this->gm.shakeAmount * 0.05f + 0.75f);
	this->shader.setUniform("texture_inverse", 0.002f);
	this->win.draw(UISprite, rs);
	this->win.display();
}

void Window::shake()
{
	this->gm.shakeAmount = 20 * this->gm.getSoundInfo()->getBassLevel() + 1;
}

void Window::getEvents()
{
	sf::Event ev;
	while (this->win.pollEvent(ev))
	{
		this->gm.processEvent(ev);
		switch (ev.type)
		{
		case sf::Event::Closed:
			this->close();
			break;
		case sf::Event::MouseMoved:
			if (this->gm.player != nullptr)
				this->gm.player->setMousePos(sf::Mouse::getPosition(this->win));
			this->gm.setMousePos(sf::Mouse::getPosition(this->win));
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
		case sf::Event::Resized:
			this->setSize(sf::Vector2u(ev.size.width, ev.size.height));
			break;
		default:
			break;
		}
		this->gm.processEvent(ev);
	}
}

void Window::registerKey(int code, bool state)
{
	switch (code)
	{
	case sf::Keyboard::F11:
		if (state) this->toogleFullscreen();
		break;
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
	if (this->gm.player != nullptr)
		this->gm.player->setKeys(this->keys);
}

void Window::toogleFullscreen()
{
	if (this->isFullscreen)
		this->setSize(this->size);
	else this->setSize(sf::Vector2u());
}

void Window::kickPlayer()
{
	if (this->gm.player == nullptr) return;
	this->gm.player->kick(this->dt);
	if (this->kickTimeout > 0.2) {
		this->kickTimeout = 0;
		this->pMan->addKickParticles(this->gm.player->getPos());
	}
	if (this->gm.player->getLife() == 0)
	{
		for (unsigned int i = 0; i < this->enemies.size(); i++)
		{

			this->pMan->addCrushParticles(this->enemies[i]->getPos());
			delete this->enemies[i];
		}
		this->enemies.clear();
		this->gm.getSoundBoard()->stopMusic();
		SceneGenerator::generateDeadScene();
		this->gm.score = 0;
	}
}

Window::~Window()
{
	if (this->gm.player != nullptr)
		delete this->gm.player;
	if (this->pMan != nullptr)
		delete this->pMan;
}