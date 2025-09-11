#pragma once

using i64 = __int64;

class TImer
{
public:
	TImer();

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

