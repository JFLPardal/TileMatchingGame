#pragma once

/*
	UIManager is responsible for holding the UI Elements
	of the game
*/

class IEventData;
class UIElement;
class Renderer;

class UIManager
{
public:
	UIManager();

	void ClearUI();
	void Draw(Renderer* renderer);
private:

	void RemoveUIElement(IEventData& eventInfo);
	void AddUIElement(IEventData& eventInfo);

	std::vector<UIElement*> m_UIElements;
};