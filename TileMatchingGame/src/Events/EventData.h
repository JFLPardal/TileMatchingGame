#pragma once
#include "Enums.h"
#include "IEventData.h"

/*
	EventData encapsulates SDL_Event and exposes the 
	relevant methods for retrieving data
*/

class EventData : public IEventData
{
public:
	EventData();

	// WARNING: this function should only be called by 'EventHandler::ProcessEventsImpl()'
	SDL_Event& GetEvent();

	Uint32 GetType() const;
	Sint32 GetUserEvent() const;
	void* GetUserEventData1() override;
	void* GetUserEventData2() override;

	Uint8 KeyPressed() override;
	Uint8 MouseButtonPressed() override;
private:
	SDL_Event m_event;
};