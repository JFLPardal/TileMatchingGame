#pragma once

/*
	EventData encapsulates SDL_Event and exposes the 
	relevant methods for retrieving data
*/

class EventData
{
public:
	EventData();
private:
	SDL_Event* m_event;
};