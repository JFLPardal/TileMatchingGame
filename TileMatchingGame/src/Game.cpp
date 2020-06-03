#include "pch.h"
#include "Game.h"
#include "Constants.h"

#include "Events/EventHandler.h"
#include "Events/UserEvent.h"
#include "MatrixGrid.h"
#include "Renderer.h"
#include "PairOfPieces.h"
#include "PointSystem.h"
#include "GameMode.h"
#include "QueueOfNextPairs.h"
#include "Events/IEventData.h"
#include "Utils.h"
#include "Window.h"
#include "UIManager.h"

Game::Game()
	: m_window(std::make_unique<Window>())
	, m_renderer(std::make_unique<Renderer>(m_window.get()))
	, m_pointSystem(std::make_unique<PointSystem>())
	, m_UIManager(std::make_unique<UIManager>())
	, m_grid(std::make_unique<MatrixGrid>())
	, m_gameMode(std::make_unique<GameMode>())
	, m_queueOfNextPairs(std::make_unique<QueueOfNextPairs>(m_grid->GetColumnAvailability()))
{
	SubscribeToEvents();
}

void Game::SpawnPairOfPieces()
{
	m_currenPair = m_queueOfNextPairs->GetPairToBeSpawned(m_grid->GetColumnAvailability());
	m_currenPair->SetActive();
}

void Game::RestartGame(RestartCondition aRestartCondition)
{
	if (aRestartCondition == RestartCondition::levelCompleted)
		m_textToDisplay = Consts::LEVEL_COMPLETED_TEXT;
	else
		m_textToDisplay = Consts::GAME_LOST_TEXT;
	Draw(); // this will guarantee that UI gets drawn before the game is reset
	Delay(2000);

	m_currenPair = nullptr;
	InitGrid();
	m_UIManager->ClearUI();

	if (aRestartCondition == RestartCondition::levelCompleted)
	{
		m_pointSystem->Reset();
		m_currentLevel++;
	}
	else if(aRestartCondition == RestartCondition::levelFailed)
	{
		InitPointSystem();
		m_currentLevel = 1;
	}
	m_textToDisplay.clear();
}

void Game::SubscribeToEvents()
{
	EventHandler::SubscribeToEvent(DefaultEventType::quit, [this](IEventData&){m_isRunning = false; });
}

void Game::Update(Uint32 msSinceLastUpdate)
{
	m_msSinceLastUpdate = msSinceLastUpdate;
	UserEvent frameStarted(UserEventType::newFrame, &m_msSinceLastUpdate);
	
	if (!m_gameMode->LevelWon() && !m_gameMode->GameLost())
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
	else if (m_gameMode->LevelWon())
	{
		RestartGame(RestartCondition::levelCompleted);
		m_gameMode->Reset();
	}
	else if (m_gameMode->GameLost()) 
	{
		RestartGame(RestartCondition::levelFailed);
		m_gameMode->Reset();
	}
}

void Game::Draw()
{
	m_renderer->ClearScreen(); 

	m_renderer->DrawBackground();
	m_queueOfNextPairs->Draw(m_renderer.get());
	m_grid->Draw(m_renderer.get());
	if (m_currenPair != nullptr) m_currenPair->Draw(m_renderer.get());
	m_UIManager->Draw(m_renderer.get());
	// text
	if (!m_textToDisplay.empty()) m_renderer->DrawText(m_textToDisplay, Vector2(Consts::TEXT_INITIAL_X, Consts::TEXT_INITIAL_Y), Vector2(Consts::TEXT_W, Consts::TEXT_H));
	m_renderer->DrawText(Consts::CURRENT_LEVEL_TEXT, Vector2(50,0), Vector2(120, 50));
	m_renderer->DrawText(std::to_string(m_currentLevel), Vector2(165,5), Vector2(20, 40));	
	
	m_renderer->Display();
}

void Game::InitPointSystem()
{
	m_pointSystem = std::make_unique<PointSystem>();
}

void Game::InitGrid()
{
	m_grid = std::make_unique<MatrixGrid>();
}

Game::~Game()
{
	SDL_Quit();
}