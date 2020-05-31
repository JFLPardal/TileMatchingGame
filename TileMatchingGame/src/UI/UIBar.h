#pragma once
#include "Rect.h"
#include "Enums.h"
#include "UIElement.h"

/*
	UIBar encapsulates the representation of a UIBar,
	exposing the relevant methods interactions with it
*/

class UIBar : public UIElement
{
public:
	UIBar(const Vector2& positionOfTopLeftCorner, const Vector2& dimensions, const Vector2& textureCoords);

	void Draw(Renderer* renderer) override;
	
	void Resize(CoordToResize coord, float percentageOfOriginalSize);
private:
	Vector2 m_currentDimensions;
	Vector2 m_originalDimensions;
	Rect m_textureRect;
};