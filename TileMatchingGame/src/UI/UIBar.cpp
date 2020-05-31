#include "pch.h"
#include "UIBar.h"
#include "Constants.h"

#include "Renderer.h"

UIBar::UIBar(const Vector2& positionOfTopLeftCorner, const Vector2& dimensions, const Vector2& textureCoords)
	: UIElement(positionOfTopLeftCorner)
	, m_originalDimensions(dimensions)
	, m_textureRect(textureCoords.X() * Consts::TEX_TILE_W, textureCoords.Y()* Consts::TEX_TILE_H, Consts::TEX_TILE_W, Consts::TEX_TILE_H)
{
	m_currentDimensions = m_originalDimensions;
}

void UIBar::Draw(Renderer* aRenderer)
{
	aRenderer->DrawUI(&m_textureRect, m_position, m_currentDimensions);
}

void UIBar::Resize(CoordToResize coord, float percentageOfOriginalSize)
{
	assert(percentageOfOriginalSize < 2.f && percentageOfOriginalSize > -.001f);
	if		(coord == CoordToResize::x) m_currentDimensions.SetX(m_originalDimensions.X() * percentageOfOriginalSize);
	else if (coord == CoordToResize::y) m_currentDimensions.SetY(m_originalDimensions.Y() * percentageOfOriginalSize);
}