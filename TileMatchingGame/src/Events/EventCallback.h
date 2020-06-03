#pragma once
#include "Alias.h"
/*
	EventCallback hides the implementation of how
	the callback functions of the events are represented
	and implemented
*/

template <typename T>
class EventCallback
{
public:
	void SubscribeToEvent(T eventType, CallbackFunctionSignature callbackFunction);
	void TriggerEvent(SDL_Event& eventType);
private:
	std::map<T, std::unique_ptr<std::vector<CallbackFunctionSignature>>> m_eventToCallback;
};

template<typename T>
void EventCallback<T>::SubscribeToEvent(T aEventType, CallbackFunctionSignature aCallbackFunction)
{
	auto result = m_eventToCallback.find(aEventType);
	if (result == m_eventToCallback.end())
	{
		m_eventToCallback.emplace(aEventType, std::make_unique<std::vector<CallbackFunctionSignature>>());
	}
	if(m_eventToCallback.at(aEventType)->size() > 0)
		m_eventToCallback.at(aEventType)->pop_back();
	m_eventToCallback.at(aEventType)->emplace_back(aCallbackFunction);
}

template<typename T>
inline void EventCallback<T>::TriggerEvent(SDL_Event& aEventType)
{
	T eventType = static_cast<T>(aEventType.user.code);
	std::for_each(m_eventToCallback.at(eventType).get()->begin(),
				m_eventToCallback.at(eventType).get()->end(),
				[&aEventType](CallbackFunctionSignature& functionToCall)
				{
					functionToCall(aEventType);
				}
	);
}

template<>
inline void EventCallback<SDL_EventType>::TriggerEvent(SDL_Event& aEventType)
{
		SDL_EventType eventType = static_cast<SDL_EventType>(aEventType.type);
		std::for_each(m_eventToCallback.at(eventType).get()->begin(),
					m_eventToCallback.at(eventType).get()->end(),
					[&aEventType](CallbackFunctionSignature& functionToCall)
					{
						functionToCall(aEventType);
					}
		);
}
