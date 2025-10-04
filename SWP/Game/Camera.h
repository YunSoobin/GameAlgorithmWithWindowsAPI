#pragma once

class Camera
{
public:
	static Camera& Handler() { static Camera g = {}; return g; }

	void Reset(int width, int height);
	void Update(float dt);

	void Shake(float power, float time);

	Vector2f GetCamRatio();

public:
	Vector2f camPos;

private:
	Vector2f _animatedPos, _shakeRatio;
	float _w2, _h2;
	float _camSpeed;
	float _shakeTime, _shakePower;
};

