#include "pch.h"
#include "FillableUIBar.h"
#include "Constants.h"

#include "Renderer.h"
#include "UIBar.h"
#include "Events/EventHandler.h"
#include "Events/UserEvent.h"

FillableUIBar::FillableUIBar(UserEventType aEventThatWillFillBar, unsigned int aBarMaxCapacity, const Vector2& aPosition, const Vector2& textureCoordForFillBar, UserEventType aEventToTriggerWhenBarIsFull)
	: m_foreground(std::make_unique<UIBar>(aPosition, Vector2(Consts::UI_BAR_W, Consts::UI_BAR_H), textureCoordForFillBar))
	, m_background(std::make_unique<UIBar>(aPosition, Vector2(Consts::UI_BAR_W, Consts::UI_BAR_H), Vector2(Consts::UI_BAR_BACKGROUND_X, Consts::UI_BAR_BACKGROUND_Y)))
	, m_maxCapacity(aBarMaxCapacity)
	, m_eventToTriggerWhenFull(aEventToTriggerWhenBarIsFull)
{
	m_foreground->Resize(CoordToResize::x, 0); // bar starts empty
	EventHandler::SubscribeToEvent(aEventThatWillFillBar, EVENT_CALLBACK(FillableUIBar::FillMethod));
}

void FillableUIBar::FillMethod(SDL_Event& aEvent)
{
	int fillIncrement = *static_cast<int*>(aEvent.user.data1);
	m_currentCapacity = std::min(m_currentCapacity + fillIncrement, m_maxCapacity);
	float currentCapacityAsPercentage = static_cast<float>(m_currentCapacity) / m_maxCapacity;

	m_foreground->Resize(CoordToResize::x, currentCapacityAsPercentage);
	if ((currentCapacityAsPercentage * 100) >= 100)
	{
		UserEvent barIsFull(m_eventToTriggerWhenFull);
	}
}

// needed on the cpp because of the forward decl of UIBar
FillableUIBar::~FillableUIBar() = default;
