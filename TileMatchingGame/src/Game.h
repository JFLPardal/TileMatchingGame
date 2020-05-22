#pragma once

/*
	Game will have the functionality to start and update the game
	and it will be responsible for telling main when the 
	program should close
*/

struct SDL_Window;
class IGridRepresentation;
class Renderer;
class PairOfPieces;

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
	void InitWindow();
	void InitRenderer();
	void SpawnPairOfPieces();

	bool m_isRunning = true;
	std::unique_ptr<IGridRepresentation> m_grid{ nullptr };
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window { nullptr, SDL_DestroyWindow };
	std::unique_ptr<Renderer> m_renderer{ nullptr };
	std::unique_ptr<PairOfPieces> m_currenPair{ nullptr };
	
};