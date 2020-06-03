#include "pch.h"
#include "UIManager.h"

#include "UI/UIElement.h"
#include "Events/IEventData.h"
#include "Events/EventHandler.h"
#include "Renderer.h"
#include "Enums.h"

UIManager::UIManager()
{
	EventHandler::SubscribeToEvent(UserEventType::UIElementCreated, EVENT_CALLBACK(UIManager::AddUIElement));
	EventHandler::SubscribeToEvent(UserEventType::UIElementDestroyed, EVENT_CALLBACK(UIManager::RemoveUIElement));
}

void UIManager::ClearUI()
{
	m_UIElements.clear();
}

void UIManager::Draw(Renderer* aRenderer)
{
	for (auto& uiElement : m_UIElements)
	{
		if (uiElement != nullptr) uiElement->Draw(aRenderer);
	}
}


void UIManager::AddUIElement(IEventData& eventInfo)
{
	auto uiElement = static_cast<UIElement*>(eventInfo.GetEventData1());
	m_UIElements.emplace_back(uiElement);
	printf("added uielement to Game refs\n");
}

void UIManager::RemoveUIElement(IEventData& eventInfo)
{
	auto UIElementToRemove = static_cast<UIElement*>(eventInfo.GetEventData1());
	auto iteratorToRemove = std::find_if(m_UIElements.begin(), m_UIElements.end(),
		[&UIElementToRemove](UIElement* m_UIElement) {return *m_UIElement == *UIElementToRemove; });
	if (iteratorToRemove != m_UIElements.end())
		m_UIElements.erase(iteratorToRemove);
}
