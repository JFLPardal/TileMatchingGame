#include "pch.h"

bool Init();
std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> LoadImage();
void Close();

std::unique_ptr<SDL_Window, decltype(&SDL_DestroyWindow)>	window(nullptr, SDL_DestroyWindow);
std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)>	imageSurface(nullptr, SDL_FreeSurface);
SDL_Surface* screenSurface = nullptr;


int main(int argc, char* args[])
{
	if (Init())
	{
		imageSurface = LoadImage();
		SDL_BlitSurface(imageSurface.get(), NULL, screenSurface, NULL);
		SDL_UpdateWindowSurface(window.get());
		SDL_Delay(2000);
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
			//SDL_Delay(2000);
		}
		else
		{
			printf("window was not created\n");
			success = false;
		}
	}
	return success;
}

std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> LoadImage()
{
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> optimizedSurface(nullptr, SDL_FreeSurface);

	imageSurface.reset(IMG_Load("player_sheet.png"));

	if (imageSurface == nullptr)
	{
		printf("no image %s\n", SDL_GetError());
	}
	else
	{
		optimizedSurface.reset(SDL_ConvertSurface(imageSurface.get(), screenSurface->format, 0));
		if (optimizedSurface == nullptr)
			printf("Unable to optimize image. SDL Error: %s", SDL_GetError());
	}

	return std::move(optimizedSurface);
}

void Close()
{
	SDL_Quit();
}