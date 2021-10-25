#include "Hider.h"
#include <Windows.h>

void Hider::hide()
{
	ShowWindow(GetConsoleWindow(), SW_HIDE);
}