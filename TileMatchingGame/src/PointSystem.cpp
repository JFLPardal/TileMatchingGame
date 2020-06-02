#include "pch.h"
#include "PointSystem.h"
#include "Enums.h"

#include "UI\FillableUIBar.h"
#include "Events\EventHandler.h"
#include "Events\UserEvent.h"

PointSystem::PointSystem()
{
	EventHandler::SubscribeToEvent(UserEventType::groupDestroyed, 
					std::function<void(SDL_Event&)>(std::bind(&PointSystem::AddPoints, this, std::placeholders::_1)));
	Init();
}

void PointSystem::Init()
{
	Reset();
}

void PointSystem::Reset()
{
	m_currentPoints = 0;
	m_levelProgressBar = std::make_unique<FillableUIBar>(UserEventType::pointsUpdated, m_pointsToClearLevel, Vector2(50,50), Vector2(10, 6), UserEventType::pointsForLevelReached);
	m_timeProgressBar = std::make_unique<FillableUIBar>(UserEventType::newFrame, Consts::MS_TO_LOSE_GAME, Vector2(50, 100), Vector2(12, 6), UserEventType::timeRanOut);
}

void PointSystem::AddPoints(SDL_Event& eventInfo)
{
	int numberOfDeletedPieces = *static_cast<int*>(eventInfo.user.data1);
	m_lastPointsAdded = numberOfDeletedPieces * 10;
	m_currentPoints += m_lastPointsAdded;
	UserEvent pointsUpdated(UserEventType::pointsUpdated, &m_lastPointsAdded);

	printf("total points: %d\n", m_currentPoints);
	if (m_currentPoints >= m_pointsToClearLevel)
	{
		m_pointsToClearLevel += Consts::POINTS_TO_CLEAR_LVL_INC;
	}
}

// needed on the cpp because of the forward decl of FillableUI
PointSystem::~PointSystem() = default;