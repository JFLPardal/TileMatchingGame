#include "pch.h"
#include "EventTest.h"

#include "EventHandler.h"
#include "Enums.h"


EventTest::EventTest()
{
	EventHandler::SubscribeToEvent(UserEventType::testType, 
				std::function<void(void*, void*)>(std::bind(&EventTest::CallbackTest, this, std::placeholders::_1, std::placeholders::_2)));
}

void EventTest::CallbackTest(void* a, void* b)
{
	printf("callback test with x data = %d \n", static_cast<EventData*>(a)->x);
}
