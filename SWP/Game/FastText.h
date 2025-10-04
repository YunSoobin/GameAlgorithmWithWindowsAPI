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

protected:
	COLORREF _textColor = 0, _bkColor = 0;
	bool _isTransparency = false;
	Vector2f _fontSize = {};
};

