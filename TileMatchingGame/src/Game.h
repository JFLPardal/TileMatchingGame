#pragma once

/*
	Game will have the functionality to start and update the game
	and it will be responsible for telling main when the 
	program should close
*/

struct SDL_Window;
struct SDL_Surface;
class IGridRepresentation;

class Game
{
public:
	Game();
	~Game();
	
	bool IsRunning() { return m_isRunning; }
	void Update(Uint32 msSinceLastUpdate);
	void Draw();
	
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
private:
	auto LoadTexture(const std::string& texturePath);

	void InitWindow();
	void InitRenderer();

	bool m_isRunning = true;

	std::unique_ptr<IGridRepresentation> m_grid;
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window{ nullptr, SDL_DestroyWindow };
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> m_imageSurface{ nullptr, SDL_FreeSurface };
	SDL_Surface* m_screenSurface{ nullptr };

	SDL_Renderer* m_renderer{ nullptr };
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> m_texture{ nullptr, SDL_DestroyTexture };
};