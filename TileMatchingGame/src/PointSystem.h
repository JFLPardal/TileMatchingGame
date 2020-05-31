#pragma once
#include "Constants.h"

/*
	PointSystem is responsible for keeping the player's score
	and to trigger an event when the player scored enough points
	to clear a level.
*/

class FillableUIBar;

class PointSystem 
{
public:
	PointSystem();
	~PointSystem();

	void Reset();
private:
	void AddPoints(SDL_Event& eventInfo);
	void Init();

	unsigned int m_pointsToClearLevel = Consts::POINTS_TO_CLEAR_1ST_LVL;
	unsigned int m_currentPoints = 0;
	unsigned int m_lastPointsAdded = 0; // needed for the UserEventType::PointsUpdated
	std::unique_ptr<FillableUIBar> m_levelProgressBar{ nullptr };
};