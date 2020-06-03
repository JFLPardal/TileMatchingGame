#pragma once

/*
	Window encapsulates SDL_Window, exposing the 
	relevant functionality for the rest of the game
*/

class Window
{
public:
	Window();

	SDL_Window* const GetSDLWindow() { return m_window.get(); }
private:
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{ nullptr, SDL_DestroyWindow };
};