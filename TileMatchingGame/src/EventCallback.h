#pragma once

/*
	EventCallback hides the implementation of how
	the callback functions of the events are represented
	and implemented
*/

template <typename T>
class EventCallback
{
public:
	void SubscribeToEvent(T eventType, std::function<void(void*, void*)> callbackFunction);
	void TriggerEvent(SDL_Event& eventType);
private:
	std::map<T, std::unique_ptr<std::vector<std::function<void(void*, void*)>>>> m_eventToCallback;
};

template<typename T>
void EventCallback<T>::SubscribeToEvent(T aEventType, std::function<void(void*, void*)> aCallbackFunction)
{
	auto result = m_eventToCallback.find(aEventType);
	if (result == m_eventToCallback.end())
	{
		m_eventToCallback.emplace(aEventType, std::make_unique<std::vector<std::function<void(void*, void*)>>>());
	}
	if(m_eventToCallback.at(aEventType)->size() > 0)
		m_eventToCallback.at(aEventType)->pop_back();// emplace_back(aCallbackFunction);
	m_eventToCallback.at(aEventType)->emplace_back(aCallbackFunction);// emplace_back(aCallbackFunction);
}

template<typename T>
inline void EventCallback<T>::TriggerEvent(SDL_Event& aEventType)
{
	printf("event triggered\n");
	T eventType = static_cast<T>(aEventType.user.code);
	std::for_each(m_eventToCallback.at(eventType).get()->begin(),
		m_eventToCallback.at(eventType).get()->end(),
		[&aEventType](std::function<void(void*, void*)>& functionToCall)
		{
			functionToCall(aEventType.user.data1, aEventType.user.data2);
		}
	);
}

template<>
inline void EventCallback<SDL_EventType>::TriggerEvent(SDL_Event& aEventType)
{
	printf("event triggered\n");
		SDL_EventType eventType = static_cast<SDL_EventType>(aEventType.type);
		std::for_each(m_eventToCallback.at(eventType).get()->begin(),
					m_eventToCallback.at(eventType).get()->end(),
					[&aEventType](std::function<void(void*, void*)>& functionToCall)
					{
				if (functionToCall)
				{
				auto das = aEventType.key.keysym.sym;
					void* arg = &das;
						functionToCall(arg, aEventType.user.data2);

				}
					}
		);
}
