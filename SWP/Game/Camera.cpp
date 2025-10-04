#include "stdafx.h"
#include "Camera.h"

void Camera::Reset(int width, int height)
{
	camPos = _animatedPos = _shakeRatio = {};
	_camSpeed = 3.0F;

	_shakeTime = _shakePower = 0.0F;

	_w2 = width * 0.5F;
	_h2 = width * 0.5F;
}

void Camera::Update(float dt)
{
	_animatedPos.x = LinearInterpolation(_animatedPos.x, camPos.x, dt * _camSpeed);
	_animatedPos.y = LinearInterpolation(_animatedPos.y, camPos.y, dt * _camSpeed);

	if (_shakeTime > 0.0F)
	{
		const float r = GetRandomValuef(0.0F, _shakePower);
		const float theta = GetRandomValuef(0.0F, 2.0F * kPi);
		_shakeRatio = { r * std::cosf(theta), r * std::sinf(theta) };

		_shakeTime -= dt;
	}
	else
	{
		_shakeTime = 0.0F;
		_shakeRatio = {};
	}
}

void Camera::Shake(float power, float time)
{
	_shakeRatio = {};
	_shakePower = power;
	_shakeTime = time;
}

Vector2f Camera::GetCamRatio()
{
	return { _w2 - _animatedPos.x - _shakeRatio.x, _h2 - _animatedPos.y - _shakeRatio.y };
}
