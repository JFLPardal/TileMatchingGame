#include "pch.h"
#include "PointSystem.h"

#include "EventHandler.h"
#include "UserEvent.h"
#include "Enums.h"

PointSystem::PointSystem()
{
	EventHandler::SubscribeToEvent(UserEventType::groupDestroyed, 
					std::function<void(SDL_Event&)>(std::bind(&PointSystem::AddPoints, this, std::placeholders::_1)));
}

void PointSystem::ResetPoints()
{
	m_currentPoints = 0;
}

void PointSystem::AddPoints(SDL_Event& eventInfo)
{
	auto numberOfDeletedPieces = static_cast<int*>(eventInfo.user.data1);
	m_currentPoints += *numberOfDeletedPieces * 10;
	printf("total points: %d\n", m_currentPoints);
	if (m_currentPoints >= m_pointsToClearLevel)
	{
		UserEvent levelComplete(UserEventType::levelCompleted);
		m_pointsToClearLevel += Consts::POINTS_TO_CLEAR_LVL_INC;
	}
}
