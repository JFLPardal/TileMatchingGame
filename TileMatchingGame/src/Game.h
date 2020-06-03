#pragma once
#include "Enums.h"
/*
	Game will have the functionality to start and update the game
	and it will be responsible for telling main when the 
	program should close
*/

//struct SDL_Window;
class IGridRepresentation;
class Renderer;
class PairOfPieces;
class PointSystem;
class UIElement;
class GameMode; 
class QueueOfNextPairs;
class IEventData;
class Window;
class UIManager;

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
	void InitPointSystem();
	void InitGrid();
	void SubscribeToEvents();
	void SpawnPairOfPieces();

	void RestartGame(RestartCondition condition);

	bool m_isRunning = true; 
	Uint32 m_msSinceLastUpdate = 0;	// event related
	std::string m_textToDisplay = "";
	int m_currentLevel = 1;

	std::unique_ptr<PointSystem> m_pointSystem{ nullptr };
	std::unique_ptr<IGridRepresentation> m_grid{ nullptr };
	std::unique_ptr<Window> m_window{ nullptr };
	std::unique_ptr<Renderer> m_renderer{ nullptr };
	std::unique_ptr<PairOfPieces> m_currenPair{ nullptr }; 
	std::unique_ptr<UIManager> m_UIManager{ nullptr };
	std::unique_ptr<GameMode> m_gameMode{ nullptr };
	std::unique_ptr<QueueOfNextPairs> m_queueOfNextPairs{ nullptr };
};