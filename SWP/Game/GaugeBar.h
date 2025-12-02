#pragma once

#include "UI.h"

class GaugeBar : public UI
{
public:
	virtual void Start(const std::string& name, const RECT& r);
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);
	
	void Animate();

	void SetEndTime(float secondsPer1);
	void SetPercentage(float percentage);
	void SetColor(COLORREF color);

private :
	COLORREF _color;
	float _t = 0.0F, _speed = 1.0F;
	bool _animated = false;
};

