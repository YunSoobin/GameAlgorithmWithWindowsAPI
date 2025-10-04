#pragma once

using i64 = __int64;

class Timer
{
public:
	static Timer& Handler() { static Timer g = {}; return g; }

	Timer();

	void Tick();
	float DeltaTime() const;

	void Reset();
	void Start();
	void Stop();

private:
	double _secondsPerCount;
	double _deltatTime;

	i64 _prevTime;
	i64 _currTime;

	bool _stopped;

};

