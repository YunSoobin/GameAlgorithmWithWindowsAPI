#pragma once

class Camera
{
public:
	static Camera& Handler() { static Camera g = {}; return g; }

	int GetWidth() const { return (int)(_w2 * 2.0F); }
	int GetHeight() const { return (int)(_h2 * 2.0F); }

	void Reset(int width, int height);
	void Update(float dt);

	void Shake(float power, float time);

	Vector2f GetCamRatio();

public:
	Vector2f camPos;
	float ratio;

private:
	Vector2f _animatedPos, _shakeRatio;
	float _w2, _h2;
	float _camSpeed;
	float _shakeTime, _shakePower;
};

