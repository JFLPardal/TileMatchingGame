#include "pch.h"
#include "EventData.h"

#include "Alias.h"

EventData::EventData()
{
	m_event = SDL_Event();
}

SDL_Event& EventData::GetEvent()
{
	return m_event;
}

Sint32 EventData::GetUserEvent() const
{
	return m_event.user.code;
}

void* EventData::GetEventData1()
{
	return m_event.user.data1;
}

void* EventData::GetUserEventData2()
{
	return m_event.user.data2;
}

Uint8 EventData::KeyPressed()
{
	return m_event.key.keysym.sym;
}

Uint8 EventData::MouseButtonPressed()
{
	return m_event.button.button;
}

Uint32 EventData::GetType() const
{
	return m_event.type;
}
