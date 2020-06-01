#pragma once

/*
	GameMode encapsulate the representation of the win and
	lose condition of the game
*/

class GameMode
{
public:
	GameMode();

	bool LevelWon() const { return m_WinConditionIsSatisfied; }
	bool GameLost() const { return m_LoseConditionIsSatisfied; }

	void Reset();
private:
	void LoseGame(SDL_Event& eventInfo);
	void WinLevel(SDL_Event& eventInfo);

	bool m_WinConditionIsSatisfied = false;
	bool m_LoseConditionIsSatisfied = false;
};