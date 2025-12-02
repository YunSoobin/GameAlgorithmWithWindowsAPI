#include "stdafx.h"
#include "GaugeBar.h"

void GaugeBar::Start(const std::string& name, const RECT& r)
{
	_r = r;
}

void GaugeBar::Update(float dt)
{
	if (!_animated)
		return;

	UI::Update(dt);

	_t += dt * _speed;
	if (_t >= 1.0F)
		_animated = false;
}

void GaugeBar::Draw(HDC hdc)
{
	if (!_animated)
		return;

	UI::Draw(hdc);

	int center_x = (int)((_r.right + _r.left) * 0.5F);
	int center_y = (int)((_r.bottom + _r.top) * 0.5F);
	int radius = max((_r.right - _r.left) * 0.5F, (_r.bottom - _r.top) * 0.5F);
	float theta = LinearInterpolation(-0.5F * kPi, 1.5F * kPi, _t);

	HPEN pen = CreatePen(PS_SOLID, 1, _color);
	HBRUSH brush = CreateSolidBrush(_color);

	SelectObject(hdc, pen);
	SelectObject(hdc, brush);

	Pie(hdc, _r.left, _r.top, _r.right, _r.bottom, center_x, _r.top, center_x + cosf(theta) * radius, center_y + sinf(theta) * radius);

	DeleteObject(pen);
	DeleteObject(brush);
}

void GaugeBar::Animate()
{
	_animated = true;
	_t = 0.0F;
}

void GaugeBar::SetEndTime(float secondsPer1)
{
	_speed = 1.0F / secondsPer1;
}

void GaugeBar::SetPercentage(float percentage)
{
	_t = percentage;
}

void GaugeBar::SetColor(COLORREF color)
{
	_color = color;
}
