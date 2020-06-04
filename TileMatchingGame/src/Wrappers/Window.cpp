#include "pch.h"
#include "Window.h"

#include "Constants.h"

Window::Window()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME,
			SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			Consts::WINDOW_W, Consts::WINDOW_H,
			SDL_WINDOW_SHOWN));
	}
	else
	{
		printf("sdl not initialized\n");
	}
}
