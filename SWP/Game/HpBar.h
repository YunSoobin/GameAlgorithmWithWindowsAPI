#pragma once

#include "UI.h"

class HpBar : public UI
{
public:
	virtual void Start(const std::string& name, const RECT& r);
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

	void SetPercentage(float percentage);
	void SetColor(COLORREF backColor, COLORREF foreColor, COLORREF widthColor, int penWidth = 1);

private:
	COLORREF _backColor, _foreColor, _widthColor;
	int _penWidth;
	float _t = 0.0F;
};

