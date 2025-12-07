#include "stdafx.h"
#include "LaserObject.h"

void LaserObject::Start()
{
}

void LaserObject::Update(float dt)
{
	if (_maxAccTime <= 0.0F)
		return;

	_currAccTime += dt;
	if (_maxAccTime < _currAccTime)
		_currAccTime = _maxAccTime;
}

void LaserObject::Draw(HDC hdc)
{
	if (_maxAccTime <= 0.0F)
		return;

	Vector2f ratio = Camera::Handler().GetCamRatio();
	HPEN pen = CreatePen(PS_SOLID, _width, _color);
	HBRUSH brush = CreateSolidBrush(_color);

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	float d = _currAccTime / _maxAccTime;
	float dstX = LinearInterpolation(position.x, _target.x, d);
	float dstY = LinearInterpolation(position.y, _target.y, d);

	DrawLine(hdc, position.x + ratio.x, position.y + ratio.y, dstX + ratio.x, dstY + ratio.y);

	DeleteObject(pen);
	DeleteObject(brush);
}

void LaserObject::Fire()
{
	_currAccTime = 0.0F;
}

void LaserObject::SetMaxTime(float maxTime)
{
	_maxAccTime = maxTime;
}

void LaserObject::SetTarget(const Vector2f& target)
{
	_target = target;
}

void LaserObject::SetLaserOpt(COLORREF color, int width)
{
	_color = color;
	_width = width;
}

void LaserObject::DrawLine(HDC hdc, int x0, int y0, int x1, int y1)
{
	MoveToEx(hdc, x0, y0, 0);
	LineTo(hdc, x1, y1);
}