#pragma once

#include "Object.h"

class LaserObject : public Object
{
public:
	virtual void Start();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

	void Fire();
	void SetMaxTime(float maxTime);
	void SetTarget(const Vector2f& target);
	void SetLaserOpt(COLORREF color, int width);

private:
	void DrawLine(HDC hdc, int x0, int y0, int x1, int y1);

private:
	Vector2f _target = {};
	float _maxAccTime = 0.0F, _currAccTime = 0.0F;
	COLORREF _color;
	int _width;
};

