#include "pch.h"
#include "Timer.h"

Timer::Timer(float wait) : _wait(wait)
{
}

bool Timer::TimerTick(float deltaTime)
{
	_sumTime += deltaTime;
	if (_sumTime < _wait)
		return false;

	return true;
}
