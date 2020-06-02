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

	EventHandler::SubscribeToEvent(UserEventType::pairOfPiecesDestroyed, [&](SDL_Event&) {m_PairOfPiecesIsValid = false; });
	EventHandler::SubscribeToEvent(UserEventType::newPairOfPiecesActive,	 [&](SDL_Event&) {m_PairOfPiecesIsValid = true; });
}

void KeyboardInputManager::KeyPressed(SDL_Event& aEventInfo)
{
	m_lastKeyPressed = aEventInfo.key.keysym.sym;
	if (m_lastKeyPressed == SDLK_a || m_lastKeyPressed == SDLK_d)
	{
		if (m_PairOfPiecesIsValid)
		{
			UserEvent movePair(UserEventType::movePairWithKeyboard, &m_lastKeyPressed);//printf("AD SUCCESFULLY RECEIVED\n");
		}
	}
}
