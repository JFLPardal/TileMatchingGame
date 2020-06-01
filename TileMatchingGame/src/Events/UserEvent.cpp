#include "pch.h"
#include "UserEvent.h"

UserEvent::UserEvent(UserEventType userEvent, void* relevantInfo, void* moreRelevantInfo)
{
	SDL_Event eventToTrigger;

	eventToTrigger.type = SDL_USEREVENT;
	eventToTrigger.user.code = static_cast<Sint32>(userEvent);
	if(relevantInfo != nullptr) eventToTrigger.user.data1 = relevantInfo;
	if(moreRelevantInfo != nullptr) eventToTrigger.user.data2 = moreRelevantInfo;
	
	SDL_PushEvent(&eventToTrigger);
}
