#include "pch.h"
#include "GameMode.h"

#include "Events/EventHandler.h"

GameMode::GameMode()
{
	EventHandler::SubscribeToEvent(UserEventType::pointsForLevelReached,	[this](IEventData&) {m_WinConditionIsSatisfied = true; });
	EventHandler::SubscribeToEvent(UserEventType::timeRanOut,				[this](IEventData&) {m_LoseConditionIsSatisfied = true; });
	EventHandler::SubscribeToEvent(UserEventType::ranOutOfGridSpace,		[this](IEventData&) {m_LoseConditionIsSatisfied = true; });
}

void GameMode::Reset()
{
	m_LoseConditionIsSatisfied = false;
	m_WinConditionIsSatisfied = false;
}