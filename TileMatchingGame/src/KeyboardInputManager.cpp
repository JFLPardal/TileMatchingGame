#include "pch.h"
#include "KeyboardInputManager.h"
#include "Enums.h"

#include "Events/EventHandler.h"
#include "Events/UserEvent.h"

bool KeyboardInputManager::m_PairOfPiecesIsValid = false;

void KeyboardInputManager::Init()
{
	Instance();
}

KeyboardInputManager& KeyboardInputManager::Instance()
{
	static KeyboardInputManager instance;
	return instance;
}

KeyboardInputManager::KeyboardInputManager()
{ 
	EventHandler::SubscribeToEvent(SDL_KEYDOWN, 
				std::function<void(SDL_Event&)>(std::bind(&KeyboardInputManager::KeyPressed, this, std::placeholders::_1)));

	EventHandler::SubscribeToEvent(SDL_MOUSEBUTTONDOWN, 
				std::function<void(SDL_Event&)>(std::bind(&KeyboardInputManager::MousePressed, this, std::placeholders::_1)));

	EventHandler::SubscribeToEvent(UserEventType::pairOfPiecesDestroyed, [this](SDL_Event&) {m_PairOfPiecesIsValid = false; });
	EventHandler::SubscribeToEvent(UserEventType::newPairOfPiecesActive, [this](SDL_Event&) {m_PairOfPiecesIsValid = true; });
}

void KeyboardInputManager::KeyPressed(SDL_Event& aEventInfo)
{
	m_lastKeyPressed = aEventInfo.key.keysym.sym;
	if (m_lastKeyPressed == SDLK_a || m_lastKeyPressed == SDLK_d)
	{
		if (m_PairOfPiecesIsValid)
		{
			UserEvent movePair(UserEventType::movePairWithKeyboard, &m_lastKeyPressed);
		}
	}
}

void KeyboardInputManager::MousePressed(SDL_Event& aEventInfo)
{
	m_lastMouseButtonPressed = aEventInfo.button.button;
	if (m_lastMouseButtonPressed == SDL_BUTTON_LEFT || m_lastMouseButtonPressed == SDL_BUTTON_RIGHT)
	{
		if (m_PairOfPiecesIsValid)
		{
			UserEvent RotatePair(UserEventType::rotatePairWithMouse, &m_lastMouseButtonPressed);
		}
	}
}
