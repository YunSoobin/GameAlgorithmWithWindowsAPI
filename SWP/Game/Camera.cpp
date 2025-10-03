#include "stdafx.h"
#include "Camera.h"

void Camera::Reset(int width, int height)
{
	camPos = {};

	_w2 = width * 0.5F;
	_h2 = width * 0.5F;
}

Vector2f Camera::GetCamRatio()
{
	return { _w2 - camPos.x, _h2 - camPos.y };
}
