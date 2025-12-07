#include "stdafx.h"
#include "RotationObject.h"

void RotationObject::Start()
{
	_shape[0] = OBJECT_SHAPE::RECTANGLE;
	_shape[1] = OBJECT_SHAPE::RECTANGLE;
	_innerTheta = _outerTheta = 0.0F;
}

void RotationObject::Update(float dt)
{
	float* theta[] = { &_outerTheta, &_innerTheta };
	float* speed[] = { &_outerSpeed, &_innerSpeed };
	for (int i = 0; i < _countof(theta); ++i)
	{
		(*theta[i]) += dt * (*speed[i]);
		if ((*theta[i]) >= 2.0F * kPi)
			(*theta[i]) = 0.0F;
	}
}

void RotationObject::Draw(HDC hdc)
{
	Vector2f ratio = Camera::Handler().GetCamRatio();
	HPEN pen = CreatePen(PS_SOLID, _width, 0);
	HBRUSH outerBrush = CreateSolidBrush(_outerColor);
	HBRUSH innerBrush = CreateSolidBrush(_innerColor);

	SelectObject(hdc, pen);
	SelectObject(hdc, outerBrush);

	float theta[] = { _outerTheta, _innerTheta };
	Vector2f newSize[] = { size, _innerSize };
	for (int i = 0; i < 2; i++)
	{
		if (_shape[i] == OBJECT_SHAPE::RECTANGLE)
		{
			DrawRotatedRectangle(hdc, newSize[i], theta[i]);
		}
		else if (_shape[i] == OBJECT_SHAPE::TRIANGLE)
		{
			DrawRotatedTriangle(hdc, newSize[i], theta[i]);
		}
		else if (_shape[i] == OBJECT_SHAPE::CIRCLE)
		{
			Ellipse(hdc, position.x - newSize[i].x + ratio.x, position.y - newSize[i].y + ratio.y, position.x + newSize[i].x + ratio.x, position.y + newSize[i].y + ratio.y);
		}

		SelectObject(hdc, innerBrush);
	}

	DeleteObject(pen);
	DeleteObject(outerBrush);
	DeleteObject(innerBrush);
}

void RotationObject::SetSize(const Vector2f& size, float innerSizeRatio)
{
	this->size = size;
	_innerSize = { innerSizeRatio * size.x, innerSizeRatio * size.y };
}

void RotationObject::SetColor(COLORREF outerColor, COLORREF innerColor, int width)
{
	_outerColor = outerColor;
	_innerColor = innerColor;
	_width = width;
}

void RotationObject::SetOriginTheta(float outerTheta, float innerTheta)
{
	_outerTheta = outerTheta;
	_innerTheta = innerTheta;
}

void RotationObject::SetRotationSpeed(float outerSpeed, float innerSpeed)
{
	_outerSpeed = outerSpeed;
	_innerSpeed = innerSpeed;
}

void RotationObject::SetShape(OBJECT_SHAPE outerShape, OBJECT_SHAPE innerShape)
{
	_shape[0] = outerShape;
	_shape[1] = innerShape;
}

void RotationObject::DrawRotatedRectangle(HDC hdc, const Vector2f& newSize, float theta)
{
	Vector2f ratio = Camera::Handler().GetCamRatio();
	Vector2f pts[4] = { {-newSize.x, -newSize.y}, {newSize.x, -newSize.y}, {newSize.x, newSize.y}, {-newSize.x, newSize.y} };
	POINT rotated_pts[4] = {};
	for (int i = 0; i < 4; ++i)
	{
		// 회전 먼저 시킨다음
		rotated_pts[i] =
		{
			(int)(std::cosf(theta) * pts[i].x) - (int)(std::sinf(theta) * pts[i].y),
			(int)(std::sinf(theta) * pts[i].x) + (int)(std::cosf(theta) * pts[i].y)
		};

		// 이동 시킨다
		rotated_pts[i] =
		{
			(int)(rotated_pts[i].x + ratio.x + position.x),
			(int)(rotated_pts[i].y + ratio.y + position.y)
		};
	}

	Polygon(hdc, rotated_pts, 4);
}

void RotationObject::DrawRotatedTriangle(HDC hdc, const Vector2f& newSize, float theta)
{
	Vector2f ratio = Camera::Handler().GetCamRatio();
	Vector2f pts[3] = { {0.0F, -newSize.y}, {newSize.x, newSize.y}, {-newSize.x, newSize.y} };
	POINT rotated_pts[3] = {};
	for (int i = 0; i < 3; ++i)
	{
		// 회전 먼저 시킨다음
		rotated_pts[i] =
		{
			(int)(std::cosf(theta) * pts[i].x) - (int)(std::sinf(theta) * pts[i].y),
			(int)(std::sinf(theta) * pts[i].x) + (int)(std::cosf(theta) * pts[i].y)
		};

		// 이동 시킨다
		rotated_pts[i] =
		{
			(int)(rotated_pts[i].x + ratio.x + position.x),
			(int)(rotated_pts[i].y + ratio.y + position.y)
		};
	}

	Polygon(hdc, rotated_pts, 3);
}
