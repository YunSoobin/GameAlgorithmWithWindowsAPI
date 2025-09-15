#pragma once

#include "UI.h"

class Text : public UI
{
public:
	virtual void Start(const std::string& name, const RECT& r) override;
	virtual void Update(float dt) override;
	virtual void Draw(HDC hdc) override;

	void SetColor(COLORREF textColor, COLORREF bkColor, bool isTransparency = false);

private:
	COLORREF textColor = 0, bkColor = 0;
	bool isTransparency = 0;

};

