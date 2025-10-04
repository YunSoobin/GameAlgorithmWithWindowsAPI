#include "stdafx.h"
#include "Timer.h"

Timer::Timer()
{
	i64 countsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	_secondsPerCount = 1.0 / (double)countsPerSec;
	_deltatTime = 0.0;
	_currTime = _prevTime = 0;
	_stopped = false;
}

void Timer::Tick()
{
	if (_stopped)
	{
		_deltatTime = 0.0;
		return;
	}

	i64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	_currTime = currTime;
	_deltatTime = (_currTime - _prevTime) * _secondsPerCount;
	_prevTime = _currTime;

	if (_deltatTime < 0.0)
		_deltatTime = 0.0;
}

float Timer::DeltaTime() const
{
	return (float)_deltatTime;
}

void Timer::Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_prevTime);
	_stopped = false;
}

void Timer::Start()
{
	if (_stopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_prevTime);
		_stopped = false;
	}
}

void Timer::Stop()
{
	if (!_stopped)
		_stopped = true;
}
