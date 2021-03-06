#include "pch.h"

#include "Game.h"
#include "Events\EventHandler.h"
#include "KeyboardInputManager.h"
#include "Enums.h"
#include "Constants.h"

void ForceFramerate(Uint32 frameStart);

int main(int argc, char* args[])
{
	auto game = std::make_unique<Game>();
	KeyboardInputManager::Init();
	Uint32 frameStart = 0;
	Uint32 lastUpdate = 0;
	srand(time(NULL));
	while (game->IsRunning())
	{
		frameStart = SDL_GetTicks();
		EventHandler::ProcessEvents();
		game->Update(SDL_GetTicks() - lastUpdate);
		lastUpdate = SDL_GetTicks();
		game->Draw();
		ForceFramerate(frameStart);
	}
	return 0;
}

void ForceFramerate(Uint32 aFrameStart)
{
	const Uint32 frameDuration = SDL_GetTicks() - aFrameStart;
	const Uint32 intendedFrameDuration = Consts::INTENDED_FRAME_DURATION;
	if (frameDuration < intendedFrameDuration)
		SDL_Delay(intendedFrameDuration - frameDuration);
}