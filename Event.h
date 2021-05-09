#pragma once
#ifdef CPPGUI_DLLMODE
struct _declspec(dllexport) EventArgs
#else
struct _declspec(dllimport)  EventArgs
#endif
{
	void *ptr;
};

struct TabChangeEventArgs
{
	class TabPage *tabpagePtr;
};

struct KeyPressedEventArgs
{
	UINT keyPressed;
};

enum EventList {
	eventNone,
	eventCheckChanged,
	eventClick,
	eventDoubleClick,
	eventClickHold,
	eventRightClick,
	eventDrag,
	eventDrop,
	eventHover,
	eventUnhover,
	eventF5Pressed,
	eventFocus,
	eventKeyPress,
	eventValueChanged,
};

#ifdef CPPGUI_DLLMODE
class _declspec(dllexport) Event
#else
class _declspec(dllimport)  Event
#endif
{
private:
	class guiObject *object;
	EventList eventName;
	std::function<void(class guiObject * sender, struct EventArgs * e)> eventAction;

	void *eventArgs;

public:

	void setEventName(EventList eventName);
	void setEventAction(std::function<void(class guiObject *sender, EventArgs *e)> eventAction);
	void setEventArgs(void *eventArgs);

	class guiObject *getEventObject();
	EventList getEventName();
	std::function<void(class guiObject *sender, struct EventArgs * e)> getEventAction();
	void *getEventArgs();

	bool equals(Event *ev);

	Event();
	Event(class guiObject *object);
	Event(EventList eventName, class guiObject *object);
};