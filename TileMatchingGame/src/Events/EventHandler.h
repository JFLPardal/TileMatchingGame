#pragma once
#include "Enums.h"
#include "EventCallback.h"
#include "Alias.h"

/*
	EventHandler is responsible for storing the callbacks for each type 
	of event that is processed by the game, wheter that is a SDL event or 
	a user defined event.

	When an event is processed and there are callbacks for that event,
	those callbacks are triggered.
*/

#define EVENT_CALLBACK(functionToCallback) CallbackFunctionSignature(std::bind(&functionToCallback, this, std::placeholders::_1))

class EventHandler
{
public:
	static void SubscribeToEvent(SDL_EventType EventType, CallbackFunctionSignature callbackFunction);
	static void SubscribeToEvent(UserEventType userEventType, CallbackFunctionSignature callbackFunction);
	static void ProcessEvents();

	EventHandler(const EventHandler&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;
private:
	EventHandler() {};
	static EventHandler& Get();

	void SubscribeToEventImpl(SDL_EventType EventType, CallbackFunctionSignature callbackFunction);
	void SubscribeToEventImpl(UserEventType userEventType, CallbackFunctionSignature callbackFunction);
	void ProcessEventsImpl();

	EventCallback<UserEventType> m_TriggerUserEvent;
	EventCallback<SDL_EventType> m_TriggerEvent;
};