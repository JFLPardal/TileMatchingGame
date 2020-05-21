#pragma once
#include "Enums.h"
#include "EventCallback.h"

/*
	EventHandler is responsible for storing the callbacks for each type 
	of event that is processed by the game, wheter that is a SDL event or 
	a user defined event.

	When an event is processed and there are callbacks for that event,
	those callbacks are triggered.
*/

class EventHandler
{
public:
	static void SubscribeToEvent(SDL_EventType EventType, std::function<void(void*, void*)> callbackFunction);
	static void SubscribeToEvent(UserEventType userEventType, std::function<void(void*, void*)> callbackFunction);
	static void ProcessEvents();

	EventHandler(const EventHandler&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;
private:
	EventHandler() {};
	static EventHandler& Get();

	void SubscribeToEventImpl(SDL_EventType EventType, std::function<void(void*, void*)> callbackFunction);
	void SubscribeToEventImpl(UserEventType userEventType, std::function<void(void*, void*)> callbackFunction);
	void ProcessEventsImpl();

	EventCallback<UserEventType> m_TriggerUserEvent;
	EventCallback<SDL_EventType> m_TriggerEvent;
};