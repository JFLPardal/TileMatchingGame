#pragma once

class EventHandler;

struct EventData
{
	EventData() : x(4), y(5) {};
	~EventData() { printf("event data deleted\n"); }
	int x = 2, y = 3;
};

class EventTest
{
public:
	EventTest();
private:
	void CallbackTest(void* a, void* b);
};