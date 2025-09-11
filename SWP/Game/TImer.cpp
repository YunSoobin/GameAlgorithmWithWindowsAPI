#include "stdafx.h"
#include "TImer.h"

TImer::TImer()
{
	i64 countsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	_secondsPerCount = 1.0 / (double)countsPerSec;
	_deltatTime = 0.0;
	_currTime = _prevTime = 0;
	_stopped = false;
}

void TImer::Tick()
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

float TImer::DeltaTime() const
{
	return (float)_deltatTime;
}

void TImer::Reset()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_prevTime);
	_stopped = false;
}

void TImer::Start()
{
	if (_stopped)
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&_prevTime);
		_stopped = false;
	}
}

void TImer::Stop()
{
	if (!_stopped)
		_stopped = true;
}
