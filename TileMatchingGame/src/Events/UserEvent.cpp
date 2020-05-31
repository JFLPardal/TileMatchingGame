#include "pch.h"
#include "UserEvent.h"

UserEvent::UserEvent(UserEventType userEvent, void* relevantInfo, void* moreRelevantInfo)
{
	SDL_Event groupDestroyed;

	groupDestroyed.type = SDL_USEREVENT;
	groupDestroyed.user.code = static_cast<Sint32>(userEvent);
	if(relevantInfo != nullptr) groupDestroyed.user.data1 = relevantInfo;
	if(moreRelevantInfo != nullptr) groupDestroyed.user.data2 = moreRelevantInfo;
	
	SDL_PushEvent(&groupDestroyed);
}
