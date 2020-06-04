#pragma once
/*
	KeyboardInputManager is responsible for triggering
	the events of keyboard keys being pressed and making sure 
	that the event can be triggered
*/

class IEventData;

class KeyboardInputManager
{
public:
	static void Init();

	KeyboardInputManager(const KeyboardInputManager&) = delete;
	KeyboardInputManager& operator=(const KeyboardInputManager&) = delete;
private:
	KeyboardInputManager();
	static KeyboardInputManager& Instance();
	void KeyPressed(IEventData& eventInfo);
	void MousePressed(IEventData& eventInfo);

	static bool m_PairOfPiecesIsValid; 
	Uint8 m_lastKeyPressed = 0;
	Uint8 m_lastMouseButtonPressed = 0;
};