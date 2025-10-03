#pragma once

#include "Text.h"

class FastText : public Text
{
public:
	virtual void Start(const std::string& name, const RECT& r) override;
	virtual void Update(float dt) override;
	virtual void Draw(HDC hdc) override;

	virtual void SetName(const std::string& name) override;
	
	void SetRect(const RECT& r);
	void SetSize(const Vector2f& size);
	void SetColor(COLORREF textColor, COLORREF bkColor, bool isTransparency = false);

private:
	COLORREF textColor = 0, bkColor = 0;
	bool isTransparency = false;
	Vector2f _fontSize = {};
};

