#include "pch.h"
#include "Game.h"
#include "Constants.h"

#include "EventHandler.h"
#include "MatrixGrid.h"
#include "Renderer.h"
#include "PairOfPieces.h"
#include "PointSystem.h"

Game::Game()
	: m_grid(std::make_unique<MatrixGrid>())
{
	InitWindow();
	InitRenderer();
	InitPointSystem();
	RegisterForLevelCompleteEvent();
	EventHandler::SubscribeToEvent(UserEventType::levelFailed, 
								std::function<void(SDL_Event&)>(std::bind(&Game::GameLost, this, std::placeholders::_1)));
}

void Game::InitWindow()
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

void Game::InitRenderer()
{
	m_renderer = std::make_unique<Renderer>(m_window.get());
}

void Game::InitPointSystem()
{
	m_pointSystem = std::make_unique<PointSystem>();
}

void Game::RegisterForLevelCompleteEvent()
{
	EventHandler::SubscribeToEvent(UserEventType::levelCompleted, [&](SDL_Event&) {m_reachedPointsToCompleteLevel = true; });
					//std::function<void(SDL_Event&)>(std::bind(&Game::RestartGame, this, std::placeholders::_1)));
}

void Game::SpawnPairOfPieces()
{
	// TODO change this to get a pair in a more sophisticated way
	m_currenPair = std::make_unique<PairOfPieces>(m_grid->GetColumnAvailability());
}

void Game::RestartGame(RestartCondition aRestartCondition)
{
	if (aRestartCondition == RestartCondition::levelCompleted)
		printf("game won!\n");
	else
		printf("game lost\n");

	SDL_Delay(2000);
	m_grid = std::make_unique<MatrixGrid>();
	m_currenPair = nullptr;

	if (aRestartCondition == RestartCondition::levelCompleted)
	{
		m_reachedPointsToCompleteLevel = false;
		m_pointSystem->ResetPoints();
	}
	else
		InitPointSystem();
}

void Game::GameLost(SDL_Event& event)
{
	RestartGame(RestartCondition::levelFailed);
}

void Game::Update(Uint32 msSinceLastUpdate)
{
	if (!m_reachedPointsToCompleteLevel)
	{
		if (m_currenPair == nullptr && m_grid->IsDoneProcessingGroups())
			SpawnPairOfPieces();
		else
		{
			if (m_currenPair != nullptr && m_grid->IsFreeInPosition(m_currenPair->GetScreenPos()))
				m_currenPair->Update(msSinceLastUpdate);
			else // one of the pieces of the pair settled
			{
				if (m_currenPair != nullptr)
					m_grid->TransferPairOwnershipToGrid(std::move(m_currenPair));
				else
					m_grid->Update(msSinceLastUpdate);
			}
		}
	}
	else
		RestartGame(RestartCondition::levelCompleted);
}

void Game::Draw()
{
	m_renderer->ClearScreen();
	m_grid->Draw(m_renderer.get());
	if(m_currenPair != nullptr) m_currenPair->Draw(m_renderer.get());
	m_renderer->Display();
}

Game::~Game()
{
	SDL_Quit();
}