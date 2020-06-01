#include "pch.h"
#include "GameMode.h"

#include "Events/EventHandler.h"

GameMode::GameMode()
{
	EventHandler::SubscribeToEvent(UserEventType::pointsForLevelReached,
								std::function<void(SDL_Event&)>(std::bind(&GameMode::WinLevel, this, std::placeholders::_1)));
	EventHandler::SubscribeToEvent(UserEventType::timeRanOut, 
								std::function<void(SDL_Event&)>(std::bind(&GameMode::LoseGame, this, std::placeholders::_1)));
	EventHandler::SubscribeToEvent(UserEventType::ranOutOfGridSpace,
								std::function<void(SDL_Event&)>(std::bind(&GameMode::LoseGame, this, std::placeholders::_1)));
}

void GameMode::Reset()
{
	m_LoseConditionIsSatisfied = false;
	m_WinConditionIsSatisfied = false;
}

void GameMode::LoseGame(SDL_Event& eventInfo)
{
	m_LoseConditionIsSatisfied = true;
}

void GameMode::WinLevel(SDL_Event& eventInfo)
{
	m_WinConditionIsSatisfied = true;
}