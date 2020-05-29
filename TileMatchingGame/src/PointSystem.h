#pragma once
#include "Constants.h"

/*
	PointSystem is responsible for keeping the player's score
	and to trigger an event when the player scored enough points
	to clear a level.
*/

class IGridRepresentation;

class PointSystem 
{
public:
	PointSystem();
	~PointSystem() { printf("point system destroyed\n"); }

	void ResetPoints();
private:
	void AddPoints(SDL_Event& eventInfo);

	unsigned int m_pointsToClearLevel = Consts::POINTS_TO_CLEAR_1ST_LVL;
	unsigned int m_currentPoints = 0;
};