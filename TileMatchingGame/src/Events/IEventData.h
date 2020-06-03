#pragma once

/*
	IEventData is an interface for 'EventData' that is 
	suppose to hide certain functionality 'EventData' has
	from classes that want to subscribe to events
*/

class IEventData
{
public:
	virtual void* GetEventData1() = 0;
	virtual void* GetUserEventData2() = 0;
	
	virtual Uint8 KeyPressed() = 0;
	virtual Uint8 MouseButtonPressed() = 0;
};