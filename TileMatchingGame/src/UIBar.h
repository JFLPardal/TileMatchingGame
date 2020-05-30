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
	~UIBar();
	
	unsigned int GetUniqueID() { return m_ID; }
	void Resize(CoordToResize coord, float percentageOfOriginalSize);
	
	void Draw(Renderer* renderer);

	bool operator==(const UIBar& barToCompareTo);
private:
	static unsigned int m_nextID;
	unsigned int m_ID = -4;
	Vector2 m_position;
	Vector2 m_currentDimensions;
	Vector2 m_originalDimensions;
	Rect m_textureRect;
};