#include "pch.h"
#include "Game.h"

#include "EventTest.h"
#include "Enums.h"
#include "Constants.h"
#include "MatrixGrid.h"
#include "Renderer.h"

void EventTesting();

Game::Game()
	: m_grid(std::make_unique<MatrixGrid>())
{
	InitWindow();
	InitRenderer();
	EventTesting();
}

void Game::InitWindow()
{
	if (SDL_Init(SDL_INIT_VIDEO) == 0)
	{
		m_window.reset(SDL_CreateWindow(Consts::WINDOW_NAME,
					SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
					Consts::WINDOW_W, Consts::WINDOW_H,
					SDL_WINDOW_SHOWN));
	}
	else
	{
		printf("sdl not initialized\n");
	}
}

void Game::InitRenderer()
{
	m_renderer = std::make_unique<Renderer>(m_window.get());
}

void Game::Update(Uint32 msSinceLastUpdate)
{
}

void Game::Draw()
{
	m_renderer.get()->ClearScreen();
	m_grid->Draw(m_renderer.get());
	m_renderer.get()->Display();
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

