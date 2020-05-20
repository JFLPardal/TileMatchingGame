#pragma once
#include "Enums.h"
/*
	EventHandler is responsible for dispatching events to
	the entities that will take care of them.

	It provides a way for any class to subscribe to a given event
	by informing the EventHandler of what function should be called
	when that event is triggered.
*/

class EventHandler
{
public:
	void SubscribeToEvent(SDL_EventType EventType, std::function<void(void*, void*)> callbackFunction);
	void SubscribeToEvent(UserEventType EventType, std::function<void(void*, void*)> callbackFunction);

	void ProcessEvents();
private:
	std::map<UserEventType, std::unique_ptr<std::vector<std::function<void(void*, void*)>>>> m_TriggerUserEvent;
	std::map<SDL_EventType, std::unique_ptr<std::vector<std::function<void(void*, void*)>>>> m_TriggerEvent;
};