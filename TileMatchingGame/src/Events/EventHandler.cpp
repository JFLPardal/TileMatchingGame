#include "pch.h"
#include "EventHandler.h"
#include "Enums.h"
#include "EventData.h"

EventHandler& EventHandler::Get()
{
	static EventHandler instance;
	return instance;
}

void EventHandler::SubscribeToEventImpl(DefaultEventType aEventType, CallbackFunctionSignature aCallbackFunction)
{
	m_TriggerEvent.SubscribeToEvent(aEventType, aCallbackFunction);
}

void EventHandler::SubscribeToEventImpl(UserEventType aEventType, CallbackFunctionSignature aCallbackFunction)
{
	if (aEventType != UserEventType::notDefined)
	{
		m_TriggerUserEvent.SubscribeToEvent(aEventType, aCallbackFunction);
	}
}

void EventHandler::ProcessEventsImpl()
{
	EventData eventToProcess;
	while (SDL_PollEvent(&eventToProcess.GetEvent()) != 0)
	{
		if (eventToProcess.GetType() == SDL_USEREVENT)
		{
			m_TriggerUserEvent.TriggerEvent(eventToProcess);
		}
		else if (eventToProcess.GetType() == SDL_QUIT 
			  || eventToProcess.GetType() == SDL_KEYDOWN
			  || eventToProcess.GetType() == SDL_MOUSEBUTTONDOWN)
		{
			m_TriggerEvent.TriggerEvent(eventToProcess);
		}
	}
}

void EventHandler::SubscribeToEvent(DefaultEventType aEventType, CallbackFunctionSignature aCallbackFunction)
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
