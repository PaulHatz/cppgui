#include "main.h"

bool Timer::timerReady()
{
	clock_t time_elapsed = MenuTime - start_time;

	if (time_elapsed >= interval) {
		start_time = MenuTime;
		return true;
	}
	
	return false;
}

Timer::Timer(clock_t interval)
{
	this->interval = interval;
	this->start_time = MenuTime;
}