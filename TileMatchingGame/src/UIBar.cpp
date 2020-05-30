#include "pch.h"
#include "UIBar.h"
#include "Constants.h"

#include "Renderer.h"

UIBar::UIBar()
	: m_position(50, 50)
	, m_textureRect(11 * Consts::TEX_TILE_W, 6 * Consts::TEX_TILE_H, Consts::TEX_TILE_W, Consts::TEX_TILE_H)
	, m_originalDimensions(220, 40)
{
	m_currentDimensions = m_originalDimensions;
}

void UIBar::Resize(CoordToResize coord, float percentageOfOriginalSize)
{
	assert(percentageOfOriginalSize < 2.f && percentageOfOriginalSize > -.001f);
	if		(coord == CoordToResize::x) m_currentDimensions.SetX(m_originalDimensions.X() * percentageOfOriginalSize);
	else if (coord == CoordToResize::y) m_currentDimensions.SetY(m_originalDimensions.Y() * percentageOfOriginalSize);
}

void UIBar::Draw(Renderer* aRenderer)
{
	aRenderer->DrawUI(&m_textureRect, m_position, m_currentDimensions);
}
