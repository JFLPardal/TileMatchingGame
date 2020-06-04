#include "pch.h"
#include "UIElement.h"
#include "Enums.h"

#include "Events\UserEvent.h"

unsigned int UIElement::m_nextID = 0;

UIElement::UIElement(const Vector2& position)
	: m_ID(m_nextID)
	, m_position(position)
{
	m_nextID++;
	UserEvent createdUIElement(UserEventType::UIElementCreated, this);
}

UIElement::~UIElement()
{
	UserEvent destroyedUIElement(UserEventType::UIElementDestroyed, this);
}

bool UIElement::operator==(const UIElement& barToCompareTo) const
{
	return m_ID == barToCompareTo.m_ID;
}

