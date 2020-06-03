#include "pch.h"
#include "EventHandler.h"
#include "Enums.h"

EventHandler& EventHandler::Get()
{
	static EventHandler instance;
	return instance;
}

void EventHandler::SubscribeToEventImpl(SDL_EventType aEventType, CallbackFunctionSignature aCallbackFunction)
{
	printf("subscribed to regular event\n");
	m_TriggerEvent.SubscribeToEvent(aEventType, aCallbackFunction);
}

void EventHandler::SubscribeToEventImpl(UserEventType aEventType, CallbackFunctionSignature aCallbackFunction)
{
	if (aEventType != UserEventType::notDefined)
	{
		printf("subscribed to user type event\n");
		m_TriggerUserEvent.SubscribeToEvent(aEventType, aCallbackFunction);
	}
}

void EventHandler::ProcessEventsImpl()
{
	SDL_Event eventToProcess;
	while (SDL_PollEvent(&eventToProcess) != 0)
	{
		if (eventToProcess.type == SDL_USEREVENT)
		{
			m_TriggerUserEvent.TriggerEvent(eventToProcess);
		}
		else if (eventToProcess.type == SDL_QUIT 
			  || eventToProcess.type == SDL_KEYDOWN
			  || eventToProcess.type == SDL_MOUSEBUTTONDOWN)
		{
			m_TriggerEvent.TriggerEvent(eventToProcess);
		}
	}
}

void EventHandler::SubscribeToEvent(SDL_EventType aEventType, CallbackFunctionSignature aCallbackFunction)
{
	Get().SubscribeToEventImpl(aEventType, aCallbackFunction);
}

void EventHandler::SubscribeToEvent(UserEventType userEventType, CallbackFunctionSignature aCallbackFunction)
{
	Get().SubscribeToEventImpl(userEventType, aCallbackFunction);
}

void EventHandler::ProcessEvents()
{
	Get().ProcessEventsImpl();
}
