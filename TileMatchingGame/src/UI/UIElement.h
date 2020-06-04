#pragma once
#include "Vector2.h"
/*
	UIElement holds the basic operations and
	data that any UI element should hold
*/

class Renderer;

class UIElement
{
public:
	UIElement(const Vector2& position);
	virtual ~UIElement();

	virtual void Draw(Renderer* renderer) = 0;

	unsigned int GetUniqueID() { return m_ID; }
	bool operator==(const UIElement& barToCompareTo) const;
protected:
	Vector2 m_position;
	static unsigned int m_nextID;
	unsigned int m_ID = -4;
};