#include "pch.h"
#include "PointSystem.h"

#include "EventHandler.h"

PointSystem::PointSystem()
{
	EventHandler::SubscribeToEvent(UserEventType::groupDestroyed, 
					std::function<void(SDL_Event&)>(std::bind(&PointSystem::AddPoints, this, std::placeholders::_1)));
}

void PointSystem::AddPoints(SDL_Event& eventInfo)
{
	auto numberOfDeletedPieces = static_cast<int*>(eventInfo.user.data1);
	m_currentPoints += *numberOfDeletedPieces * 10;
	printf("total points: %d\n", m_currentPoints);
}
