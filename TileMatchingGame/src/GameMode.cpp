#include "pch.h"
#include "GameMode.h"

#include "Events/EventHandler.h"

GameMode::GameMode()
{
	EventHandler::SubscribeToEvent(UserEventType::pointsForLevelReached, EVENT_CALLBACK(GameMode::WinLevel));
	EventHandler::SubscribeToEvent(UserEventType::timeRanOut, EVENT_CALLBACK(GameMode::LoseGame));
	EventHandler::SubscribeToEvent(UserEventType::ranOutOfGridSpace, EVENT_CALLBACK(GameMode::LoseGame));
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