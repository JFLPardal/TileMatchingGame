#pragma once

/*
	GameMode encapsulate the representation of the win and
	lose condition of the game
*/

class IEventData;

class GameMode
{
public:
	GameMode();

	bool LevelWon() const { return m_WinConditionIsSatisfied; }
	bool GameLost() const { return m_LoseConditionIsSatisfied; }

	void Reset();
private:
	bool m_WinConditionIsSatisfied = false;
	bool m_LoseConditionIsSatisfied = false;
};