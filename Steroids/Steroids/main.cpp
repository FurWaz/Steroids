#include "Window.h"

int main(int argc, char* argv[])
{
	Window win(sf::Vector2u(), "Steroids");
	while (win.isOpen())
	{
		win.getEvents();
		win.update();
		win.render();
	}
	return EXIT_SUCCESS;
}