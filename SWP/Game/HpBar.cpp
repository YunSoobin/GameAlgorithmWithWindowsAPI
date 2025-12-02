#include "stdafx.h"
#include "HpBar.h"

void HpBar::Start(const std::string& name, const RECT& r)
{
	_r = r;
}

void HpBar::Update(float dt)
{
	UI::Update(dt);

	// 임시 테스트용 코드
	_t += dt;
	if (_t >= 1.0F)
		_t = 0.0F;
}

void HpBar::Draw(HDC hdc)
{
	UI::Draw(hdc);

	Vector2f ratio = Camera::Handler().GetCamRatio();
	int right = (int)LinearInterpolation((float)_r.left, (float)_r.right, _t);  // x

	HPEN backPen = CreatePen(PS_SOLID, _penWidth, _widthColor);
	HPEN forePen = CreatePen(PS_SOLID, 1, _foreColor);
	HBRUSH backBrush = CreateSolidBrush(_backColor);
	HBRUSH foreBrush = CreateSolidBrush(_foreColor);

	SelectObject(hdc, backPen);
	SelectObject(hdc, backBrush);
	Rectangle(hdc, _r.left + ratio.x, _r.top + ratio.y, _r.right + ratio.x, _r.bottom + ratio.y);

	SelectObject(hdc, forePen);
	SelectObject(hdc, foreBrush);
	Rectangle(hdc, _r.left + _penWidth + ratio.x, _r.top + _penWidth + ratio.y, right - _penWidth + ratio.x, _r.bottom - _penWidth + ratio.y);

	DeleteObject(backPen);
	DeleteObject(forePen);
	DeleteObject(backBrush);
	DeleteObject(foreBrush);
}

void HpBar::SetPercentage(float percentage)
{
	_t = percentage;
}

void HpBar::SetColor(COLORREF backColor, COLORREF foreColor, COLORREF widthColor, int penWidth)
{
	_backColor = backColor;
	_foreColor = foreColor;
	_widthColor = widthColor;
	_penWidth = penWidth;
}