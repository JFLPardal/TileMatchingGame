#include "pch.h"
#include "PointSystem.h"

#include "EventHandler.h"
#include "UserEvent.h"
#include "Enums.h"
#include "FillableUIBar.h"

PointSystem::PointSystem()
{
	EventHandler::SubscribeToEvent(UserEventType::groupDestroyed, 
					std::function<void(SDL_Event&)>(std::bind(&PointSystem::AddPoints, this, std::placeholders::_1)));
	//InitUI();
}

void PointSystem::ResetPoints()
{
	m_currentPoints = 0;
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
		UserEvent levelComplete(UserEventType::levelCompleted);
		m_pointsToClearLevel += Consts::POINTS_TO_CLEAR_LVL_INC;
	}
}
/*
void PointSystem::InitUI()
{
	m_levelProgressBar = std::make_unique<FillableUIBar>(UserEventType::pointsUpdated, m_pointsToClearLevel);
}
*/