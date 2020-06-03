#include "pch.h"
#include "Game.h"
#include "Constants.h"

#include "Events/EventHandler.h"
#include "Events/UserEvent.h"
#include "MatrixGrid.h"
#include "Renderer.h"
#include "PairOfPieces.h"
#include "PointSystem.h"
#include "UI/UIElement.h"
#include "GameMode.h"
#include "QueueOfNextPairs.h"

Game::Game()
	: m_grid(std::make_unique<MatrixGrid>())
	, m_gameMode(std::make_unique<GameMode>())
	, m_queueOfNextPairs(std::make_unique<QueueOfNextPairs>(m_grid->GetColumnAvailability()))
{
	InitWindow();
	InitRenderer();
	InitPointSystem();
	SubscribeToEvents();
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

void Game::SpawnPairOfPieces()
{
	m_currenPair = m_queueOfNextPairs->GetPairToBeSpawned(m_grid->GetColumnAvailability());
	m_currenPair->SetActive();
}

void Game::AddUIElement(SDL_Event& eventInfo)
{
	auto uiElement = static_cast<UIElement*>(eventInfo.user.data1);
	m_UIElements.emplace_back(uiElement);
	printf("added uielement to Game refs\n");
}

void Game::RemoveUIElement(SDL_Event& eventInfo)
{
	auto UIElementToRemove = static_cast<UIElement*>(eventInfo.user.data1);
	auto iteratorToRemove = std::find_if(m_UIElements.begin(), m_UIElements.end(), 
							[&UIElementToRemove](UIElement* m_UIElement) {return *m_UIElement == *UIElementToRemove; });
	if (iteratorToRemove != m_UIElements.end())
		m_UIElements.erase(iteratorToRemove);
}

void Game::RestartGame(RestartCondition aRestartCondition)
{
	if (aRestartCondition == RestartCondition::levelCompleted)
		m_textToDisplay = Consts::LEVEL_COMPLETED_TEXT;
	else
		m_textToDisplay = Consts::GAME_LOST_TEXT;
	Draw(); // this will guarantee that UI gets drawn before the game is reset
	SDL_Delay(2000);

	m_grid = std::make_unique<MatrixGrid>();
	m_currenPair = nullptr;
	m_UIElements.clear();

	if (aRestartCondition == RestartCondition::levelCompleted)
	{
		m_pointSystem->Reset();
		m_currentLevel++;
	}
	else if(aRestartCondition == RestartCondition::levelFailed)
	{
		m_currentLevel = 1;
		InitPointSystem();
	}
	m_textToDisplay.clear();
}

void Game::SubscribeToEvents()
{
	EventHandler::SubscribeToEvent(SDL_QUIT, [this](SDL_Event){m_isRunning = false; });

	EventHandler::SubscribeToEvent(UserEventType::UIElementCreated,
								std::function<void(SDL_Event&)>(std::bind(&Game::AddUIElement, this, std::placeholders::_1)));
	
	EventHandler::SubscribeToEvent(UserEventType::UIElementDestroyed,
								std::function<void(SDL_Event&)>(std::bind(&Game::RemoveUIElement, this, std::placeholders::_1)));
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
	for (auto& uiElement : m_UIElements)
	{
		if(uiElement != nullptr) uiElement->Draw(m_renderer.get());
	}
	m_queueOfNextPairs->Draw(m_renderer.get());
	m_grid->Draw(m_renderer.get());
	if (m_currenPair != nullptr) m_currenPair->Draw(m_renderer.get());
	// text
	if (!m_textToDisplay.empty()) m_renderer->DrawText(m_textToDisplay, Vector2(Consts::TEXT_INITIAL_X, Consts::TEXT_INITIAL_Y), Vector2(Consts::TEXT_W, Consts::TEXT_H));
	m_renderer->DrawText(Consts::CURRENT_LEVEL_TEXT, Vector2(50,0), Vector2(120, 50));
	m_renderer->DrawText(std::to_string(m_currentLevel), Vector2(165,5), Vector2(20, 40));	
	
	m_renderer->Display();
}

Game::~Game()
{
	SDL_Quit();
}