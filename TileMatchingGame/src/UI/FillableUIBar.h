#pragma once
#include "Enums.h"
/*
	FillableUIBar represents a bar that can be filled (or emptied)
	according to some condition.
*/

class Renderer;
class UIBar;

class FillableUIBar
{
public:
	FillableUIBar(UserEventType eventThatWillFillBar, unsigned int barMaxCapacity);
	~FillableUIBar();

private:
	void FillMethod(SDL_Event& event);

	std::unique_ptr<UIBar> m_background;
	std::unique_ptr<UIBar> m_foreground;
	unsigned int m_maxCapacity = -7;
	unsigned int m_currentCapacity = 0;
};