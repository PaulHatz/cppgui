#pragma once
class Timer
{
private:
	clock_t start_time;
	clock_t interval;
public:
	bool timerReady();
	Timer(clock_t interval);
};

