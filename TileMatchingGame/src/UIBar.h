#pragma once
#include "Vector2.h"
#include "Rect.h"
#include "Enums.h"

/*
	UIBar encapsulates the representation of a UIBar,
	exposing the relevant methods interactions with it
*/

class Renderer;

class UIBar
{
public:
	UIBar();
	
	void Resize(CoordToResize coord, float percentageOfOriginalSize);
	void Draw(Renderer* renderer);
private:
	Vector2 m_position;
	Vector2 m_currentDimensions;
	Vector2 m_originalDimensions;
	Rect m_textureRect;
};