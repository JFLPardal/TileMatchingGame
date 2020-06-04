#include "pch.h"
#include "KeyboardInputManager.h"
#include "Enums.h"

#include "Events/EventHandler.h"
#include "Events/UserEvent.h"
#include "Events/IEventData.h"

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
	EventHandler::SubscribeToEvent(DefaultEventType::keyDown, EVENT_CALLBACK(KeyboardInputManager::KeyPressed));
	EventHandler::SubscribeToEvent(DefaultEventType::mouseButtonDown, EVENT_CALLBACK(KeyboardInputManager::MousePressed));
	EventHandler::SubscribeToEvent(UserEventType::pairOfPiecesDestroyed, [this](IEventData&) {m_PairOfPiecesIsValid = false; });
	EventHandler::SubscribeToEvent(UserEventType::newPairOfPiecesActive, [this](IEventData&) {m_PairOfPiecesIsValid = true; });
}

void KeyboardInputManager::KeyPressed(IEventData& aEventInfo)
{
	m_lastKeyPressed = aEventInfo.KeyPressed();
	if (m_lastKeyPressed == static_cast<Uint8>(KeyboardKey::a) || m_lastKeyPressed == static_cast<Uint8>(KeyboardKey::d))
	{
		if (m_PairOfPiecesIsValid)
		{
			UserEvent movePair(UserEventType::movePairWithKeyboard, &m_lastKeyPressed);
		}
	}
}

void KeyboardInputManager::MousePressed(IEventData& aEventInfo)
{
	m_lastMouseButtonPressed = aEventInfo.MouseButtonPressed();
	if (m_lastMouseButtonPressed == static_cast<int>(MouseButton::left) || m_lastMouseButtonPressed == static_cast<int>(MouseButton::right))
	{
		if (m_PairOfPiecesIsValid)
		{
			UserEvent RotatePair(UserEventType::rotatePairWithMouse, &m_lastMouseButtonPressed);
		}
	}
}
