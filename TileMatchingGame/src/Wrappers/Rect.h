#pragma once

/*
	Rect is a wrapper around SDL_Rect.
	It provides a function to get an SDL_Rect so that
	it is compatible with SDL calls
*/

class Rect
{
public:
	Rect();
	Rect(int x, int y, int w, int h);

	SDL_Rect GetAsSDLRect();
private:
	int m_x, m_y, m_w, m_h;
};