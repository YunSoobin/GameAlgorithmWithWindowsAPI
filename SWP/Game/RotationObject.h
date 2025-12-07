#pragma once

#include "Object.h"

class RotationObject : public Object
{
public:
	virtual void Start();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

	void SetSize(const Vector2f& size, float innerSizeRatio);
	void SetColor(COLORREF outerColor, COLORREF innerColor, int width = 1);
	void SetOriginTheta(float outerTheta, float innterTheta);
	void SetRotationSpeed(float outerSpeed, float innerSpeed);
	void SetShape(OBJECT_SHAPE outerShape, OBJECT_SHAPE innerShape);

private:
	void DrawRotatedRectangle(HDC hdc, const Vector2f& newSize, float theta);
	void DrawRotatedTriangle(HDC hdc, const Vector2f& newSize, float theta);

private:
	Vector2f _innerSize;
	OBJECT_SHAPE _shape[2];
	float _outerTheta, _innerTheta, _outerSpeed, _innerSpeed;
	COLORREF _outerColor, _innerColor;
	int _width;
};

