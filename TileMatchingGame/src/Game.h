#pragma once
#include "Enums.h"
/*
	Game will have the functionality to start and update the game
	and it will be responsible for telling main when the 
	program should close
*/

struct SDL_Window;
class IGridRepresentation;
class Renderer;
class PairOfPieces;
class PointSystem;
class UIElement;
class GameMode; 
class QueueOfNextPairs;

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
	void InitPointSystem();
	void SubscribeToEvents();
	void SpawnPairOfPieces();

	void AddUIElement(SDL_Event& eventInfo);
	void RemoveUIElement(SDL_Event& eventInfo);

	void RestartGame(RestartCondition condition);

	bool m_isRunning = true; 
	Uint32 m_msSinceLastUpdate = 0;
	std::string m_textToDisplay = "";

	std::unique_ptr<PointSystem> m_pointSystem{ nullptr };
	std::unique_ptr<IGridRepresentation> m_grid{ nullptr };
	std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)> m_window { nullptr, SDL_DestroyWindow };
	std::unique_ptr<Renderer> m_renderer{ nullptr };
	std::unique_ptr<PairOfPieces> m_currenPair{ nullptr }; 
	std::vector<UIElement*> m_UIElements;
	std::unique_ptr<GameMode> m_gameMode{ nullptr };
	std::unique_ptr<QueueOfNextPairs> m_queueOfNextPairs{ nullptr };
};