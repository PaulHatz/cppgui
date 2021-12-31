#include "main.h"


void Event::setEventName(EventList eventName)
{
	this->eventName = eventName;
}

void Event::setEventAction(std::function<void(class guiObject *sender, EventArgs * e)> eventAction)
{
	this->eventAction = eventAction;
}

void Event::setEventArgs(void *eventArgs)
{
	this->eventArgs = eventArgs;
}

guiObject *Event::getEventObject()
{
	return this->object;
}

EventList Event::getEventName()
{
	return this->eventName;
}

std::function<void(class guiObject *sender, EventArgs *e)> Event::getEventAction()
{
	return this->eventAction;
}

void *Event::getEventArgs()
{
	return this->eventArgs;
}

bool Event::equals(Event *ev)
{
	if (this->object == ev->getEventObject() && this->eventName == ev->getEventName())
		return true;

	return false;
}

Event::Event()
{
	this->eventName = eventNone;
	this->eventAction = nullptr;
	this->eventArgs = nullptr;

}

Event::Event(guiObject *object)
{
	this->eventName = eventNone;
	this->eventAction = nullptr;
	this->eventArgs = nullptr;
	this->object = object;
}

Event::Event(EventList eventName, guiObject *object)
{
	this->eventName = eventName;

	this->eventAction = nullptr;
	this->eventArgs = nullptr;

	this->object = object;
}
