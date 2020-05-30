#include "pch.h"
#include "Game.h"
#include "Constants.h"

#include "EventHandler.h"
#include "MatrixGrid.h"
#include "Renderer.h"
#include "PairOfPieces.h"
#include "PointSystem.h"
#include "FillableUIBar.h"
#include "UIBar.h"

Game::Game()
	: m_grid(std::make_unique<MatrixGrid>())
{
	InitWindow();
	InitRenderer();
	InitPointSystem();
	InitUI();
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
	// TODO change this to get a pair in a more sophisticated way
	m_currenPair = std::make_unique<PairOfPieces>(m_grid->GetColumnAvailability());
}

void Game::AddUIElement(SDL_Event& eventInfo)
{
	auto uiElement = static_cast<UIBar*>(eventInfo.user.data1);
	m_UIElements.emplace_back(uiElement);
	printf("added UIElement\n");
}

void Game::RemoveUIElement(SDL_Event& eventInfo)
{
	auto UIElementToRemove = *static_cast<UIBar*>(eventInfo.user.data1);
	auto iteratorToRemove = std::find_if(m_UIElements.begin(), m_UIElements.end(), 
							[&UIElementToRemove](UIBar* m_UIElement) {return *m_UIElement == UIElementToRemove; });
	if (iteratorToRemove != m_UIElements.end())
		m_UIElements.erase(iteratorToRemove);
	printf("removed UIElement\n");
}

void Game::RestartGame(RestartCondition aRestartCondition)
{
	Draw(); // this will guarantee that UI gets drawn before the game is reset
	if (aRestartCondition == RestartCondition::levelCompleted)
		printf("game won!\n");
	else
		printf("game lost\n");

	SDL_Delay(2000);
	m_grid = std::make_unique<MatrixGrid>();
	m_levelProgressBar = std::make_unique<FillableUIBar>(UserEventType::pointsUpdated, 200);
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

void Game::InitUI()
{
	m_levelProgressBar = std::make_unique<FillableUIBar>(UserEventType::pointsUpdated, 200);
}

void Game::SubscribeToEvents()
{
	EventHandler::SubscribeToEvent(UserEventType::levelCompleted, 
								[&](SDL_Event&) {m_reachedPointsToCompleteLevel = true; });

	EventHandler::SubscribeToEvent(UserEventType::levelFailed,
								std::function<void(SDL_Event&)>(std::bind(&Game::GameLost, this, std::placeholders::_1)));

	EventHandler::SubscribeToEvent(UserEventType::UIBarCreated,
								std::function<void(SDL_Event&)>(std::bind(&Game::AddUIElement, this, std::placeholders::_1)));
	
	EventHandler::SubscribeToEvent(UserEventType::UIBarDestroyed,
								std::function<void(SDL_Event&)>(std::bind(&Game::RemoveUIElement, this, std::placeholders::_1)));
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
	//m_levelProgressBar->Draw(m_renderer.get());
	for (auto& uiElement : m_UIElements)
	{
		uiElement->Draw(m_renderer.get());
	}
	m_grid->Draw(m_renderer.get());
	if(m_currenPair != nullptr) m_currenPair->Draw(m_renderer.get());
	m_renderer->Display();
}

Game::~Game()
{
	SDL_Quit();
}