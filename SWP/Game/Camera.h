#pragma once

class Camera
{
public:
	void Reset(int width, int height);

	Vector2f GetCamRatio();

public:
	Vector2f camPos;

private:
	float _w2, _h2;

};

