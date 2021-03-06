#pragma once
#include "Enums.h"

/* 
	UserEvent encapsulates the creation of a SDL_USEREVENT;
	
	The 2 void* are pointers of any information that might be useful
	for the callback function to know p.e. if a UserEventType::PlayerMoved
	is created, the pointers might point to his new position.
*/

class UserEvent
{
public:
	explicit UserEvent(UserEventType userEvent, void* relevantInfo = nullptr, void* moreRelevantInfo = nullptr);
	UserEvent() = delete;
	UserEvent(UserEvent&&) = delete;
	UserEvent(const UserEvent&) = delete;
};