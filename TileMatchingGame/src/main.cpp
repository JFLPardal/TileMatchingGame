#include "pch.h"

#include "EventHandler.h"
#include "Enums.h"

std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>	window(nullptr, SDL_DestroyWindow);
SDL_Surface* screenSurface = nullptr;

bool Init();
void Close();

struct EventData
{
	int x = 2, y = 3;
};

void Print(void* a, void* b)
{
	printf("event triggered %d \n", static_cast<EventData*>(a)->x);
}

int main(int argc, char* args[])
{
	Init();
	EventHandler eventHandler;
	eventHandler.SubscribeToEvent(UserEventType::testType, &Print);
	
	SDL_Event customEvent;
	customEvent.type = SDL_USEREVENT;
	customEvent.user.code = (Sint32) UserEventType::testType;
	EventData data;
	customEvent.user.data1 = &data;
	SDL_PushEvent(&customEvent);
	while (true)
	{
		eventHandler.ProcessEvents();
	}
	Close();
	return 0;
}

bool Init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("sdl not initialized\n");
		success = false;
	}
	else
	{
		window.reset(SDL_CreateWindow("windoooooo", 600, 300, 500, 500, SDL_WINDOW_SHOWN));
		if (window != nullptr)
		{
			screenSurface = SDL_GetWindowSurface(window.get());
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 100, 0, 200));
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 100, 0, 200));
			SDL_UpdateWindowSurface(window.get());
		}
		else
		{
			printf("window was not created\n");
			success = false;
		}
	}
	return success;
}


void Close()
{
	SDL_Quit();
}