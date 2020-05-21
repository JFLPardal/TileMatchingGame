#pragma once

class EventHandler;

struct EventData
{
	int x = 2, y = 3;
};

class EventTest
{
public:
	EventTest();
private:
	void CallbackTest(void* a, void* b);
};