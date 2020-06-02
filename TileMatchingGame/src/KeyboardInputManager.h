#pragma once
/*
	KeyboardInputManager is responsible for triggering
	the events of keyboard keys being pressed and making sure 
	that the event can be triggered
*/

class KeyboardInputManager
{
public:
	static void Init();

	KeyboardInputManager(const KeyboardInputManager&) = delete;
	KeyboardInputManager& operator=(const KeyboardInputManager&) = delete;
private:
	KeyboardInputManager();
	static KeyboardInputManager& Instance();
	void KeyPressed(SDL_Event& eventInfo);

	static bool m_PairOfPiecesIsValid; 
	Sint32 m_lastKeyPressed = 0;
};