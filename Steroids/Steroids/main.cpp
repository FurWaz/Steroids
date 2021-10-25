#include "Window.h"
#include "Hider.h"

int main(int argc, char* argv[])
{
	Hider::hide();
	Window win(sf::Vector2u(960, 540), "Steroids");
	while (win.isOpen())
	{
		win.getEvents();
		win.update();
		win.render();
	}
	return EXIT_SUCCESS;
}