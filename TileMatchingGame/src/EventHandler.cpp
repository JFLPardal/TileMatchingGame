#include "pch.h"
#include "EventHandler.h"

#include "Enums.h"


void EventHandler::SubscribeToEvent(SDL_EventType aEventType, std::function<void(void*, void*)> aCallbackFunction)
{
	printf("subscribed to regular event\n");
	auto result = m_TriggerEvent.find(aEventType);
	if (result == m_TriggerEvent.end())
	{
		m_TriggerEvent.emplace(aEventType, std::make_unique<std::vector<std::function<void(void*, void*)>>>());
	}
	m_TriggerEvent.at(aEventType).get()->emplace_back(aCallbackFunction);
}

void EventHandler::SubscribeToEvent(UserEventType aEventType, std::function<void(void*, void*)> aCallbackFunction)
{
	printf("subscribed to user type event\n");
	auto result = m_TriggerUserEvent.find(aEventType);
	if (result == m_TriggerUserEvent.end())
	{
		m_TriggerUserEvent.emplace(aEventType, std::make_unique<std::vector<std::function<void(void*, void*)>>>());
	}
	m_TriggerUserEvent.at(aEventType).get()->emplace_back(aCallbackFunction);
}

void EventHandler::ProcessEvents()
{
	SDL_Event eventToProcess;
	while (SDL_PollEvent(&eventToProcess) != 0)
	{
		if (eventToProcess.type == SDL_USEREVENT)
		{
			UserEventType typess = static_cast<UserEventType>(eventToProcess.user.code);

			std::for_each(m_TriggerUserEvent.at(typess).get()->begin(), 
						  m_TriggerUserEvent.at(typess).get()->end(),
						[&eventToProcess](std::function<void(void*, void*)>& functionToCall)
						{
							functionToCall(eventToProcess.user.data1, eventToProcess.user.data2);
						}
			);
		}
		else if (eventToProcess.type == SDL_QUIT)
		{
			SDL_EventType eventType = static_cast<SDL_EventType>(eventToProcess.type);

			std::for_each(m_TriggerEvent.at(eventType).get()->begin(),
						  m_TriggerEvent.at(eventType).get()->end(),
						[&eventToProcess](std::function<void(void*, void*)>& functionToCall)
						{
							functionToCall(eventToProcess.user.data1, eventToProcess.user.data2);
						}
			);
		}
	}
}
