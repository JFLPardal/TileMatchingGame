#include "pch.h"
#include "Game.h"

#include "EventTest.h"
#include "Enums.h"
#include "Constants.h"
#include "MatrixGrid.h"

void EventTesting();

auto Game::LoadTexture(const std::string& aTexturePath)
{
	std::unique_ptr<SDL_Texture, decltype(&SDL_DestroyTexture)> texture(nullptr, SDL_DestroyTexture);
	std::unique_ptr<SDL_Surface, decltype(&SDL_FreeSurface)> loadedSurface(IMG_Load(aTexturePath.c_str()), SDL_FreeSurface);

	if (loadedSurface.get() != nullptr)
	{
		texture.reset(SDL_CreateTextureFromSurface(m_renderer, loadedSurface.get()));
		if (texture.get() == nullptr)
		{
			printf("unable to create texture %s\n", SDL_GetError());
		}
	}
	else
		printf("unable to load image %s : %s\n", aTexturePath.c_str(), SDL_GetError());
	return texture;
}

Game::Game()
	:m_grid(std::make_unique<MatrixGrid>())
{
	InitWindow();
	InitRenderer();
	EventTesting();

	m_texture = LoadTexture("test_tilesheet.png");
}

void Game::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("sdl not initialized\n");
	}
	else
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME,
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
					Consts::WINDOW_W, Consts::WINDOW_H,
					SDL_WINDOW_SHOWN));
		if (m_window != nullptr)
		{
			m_screenSurface = SDL_GetWindowSurface(m_window.get());
		}
		else
		{
			printf("window was not created\n");
		}
	}
}

void Game::InitRenderer()
{
	m_renderer = SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED);
	if (m_renderer != nullptr)
	{
		SDL_SetRenderDrawColor(m_renderer, 100, 0, 200, 255);
	}
	else
		printf("renderer was not created %s\n", SDL_GetError());
}

void Game::Update(Uint32 msSinceLastUpdate)
{
}

void Game::Draw()
{
	SDL_RenderClear(m_renderer);
	SDL_Rect textureCoords{64,0, Consts::TEX_TILE_W,Consts::TEX_TILE_H };
	SDL_Rect screenPosAndSize{500,300, Consts::PIECE_W,Consts::PIECE_H };
	SDL_RenderCopy(m_renderer, m_texture.get(), &textureCoords, &screenPosAndSize);
	SDL_RenderPresent(m_renderer);
}

Game::~Game()
{
	SDL_Quit();
}

void EventTesting()
{
	EventTest eventTest;
	EventTest eventTest2;

	// data is deleted when the function returns, so it never reachs the callback
	// try to use RAII?
	SDL_Event customEvent;
	customEvent.type = SDL_USEREVENT;
	customEvent.user.code = (Sint32)UserEventType::testType;
	EventData data;
	customEvent.user.data1 = &data;
	SDL_PushEvent(&customEvent);
}

