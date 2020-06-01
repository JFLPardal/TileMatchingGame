#pragma once
#include "Enums.h"
#include "Vector2.h"
/*
	FillableUIBar represents a bar that can be filled (or emptied)
	when a certain UserEventType is triggered.
*/

class Renderer;
class UIBar;

class FillableUIBar
{
public:
	FillableUIBar(UserEventType eventThatWillFillBar, unsigned int barMaxCapacity, const Vector2& positionOnScreen, UserEventType eventToTriggerWhenBarIsFull = UserEventType::notDefined);
	~FillableUIBar();

private:
	void FillMethod(SDL_Event& event);

	UserEventType m_eventToTriggerWhenFull = UserEventType::notDefined;
	std::unique_ptr<UIBar> m_background;
	std::unique_ptr<UIBar> m_foreground;
	unsigned int m_maxCapacity = -7;
	unsigned int m_currentCapacity = 0;
};