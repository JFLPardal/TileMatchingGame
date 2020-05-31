#include "pch.h"
#include "FillableUIBar.h"
#include "Constants.h"

#include "Renderer.h"
#include "UIBar.h"
#include "Events\EventHandler.h"

FillableUIBar::FillableUIBar(UserEventType aEventThatWillFillBar, unsigned int aBarMaxCapacity)
	: m_foreground(std::make_unique<UIBar>())
	, m_maxCapacity(aBarMaxCapacity)
{
	m_foreground->Resize(CoordToResize::x, 0); // bar starts empty
	EventHandler::SubscribeToEvent(aEventThatWillFillBar,
									std::function<void(SDL_Event&)>(std::bind(&FillableUIBar::FillMethod, this, std::placeholders::_1)));
}

void FillableUIBar::Draw(Renderer* aRenderer)
{
	m_foreground->Draw(aRenderer);
}

void FillableUIBar::FillMethod(SDL_Event& aEvent)
{
	int fillIncrement = *static_cast<int*>(aEvent.user.data1);
	m_currentCapacity = std::min(m_currentCapacity + fillIncrement, m_maxCapacity);
	float currentCapacityAsPercentage = static_cast<float>(m_currentCapacity) / m_maxCapacity;
	printf("% : %f \n", currentCapacityAsPercentage);
	m_foreground->Resize(CoordToResize::x, currentCapacityAsPercentage);
}

// needed on the cpp because of the forward decl of UIBar
FillableUIBar::~FillableUIBar() = default;
