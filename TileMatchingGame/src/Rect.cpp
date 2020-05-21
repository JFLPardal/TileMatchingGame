#include "pch.h"
#include "Rect.h"

Rect::Rect()
	:Rect(-3,-3,-3,3)
{
}

Rect::Rect(int aX, int aY, int aW, int aH)
	: m_x(aX), m_y(aY)
	, m_w(aW), m_h(aH)
{
}

SDL_Rect Rect::GetAsSDLRect()
{
	SDL_Rect rect;
	rect.x = m_x;
	rect.y = m_y;
	rect.w = m_w;
	rect.h = m_h;
	return rect;
}
