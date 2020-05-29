#pragma once

/*
	PointSystem is responsible for keeping the player's score
	and informing 'Game' when the player scored enough points
	to clear a level.
*/

class IGridRepresentation;

class PointSystem 
{
public:
	PointSystem();
private:
	void AddPoints(SDL_Event& eventInfo);

	unsigned int m_currentPoints = 0;
};