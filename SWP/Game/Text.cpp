#include "stdafx.h"
#include "Text.h"

void Text::Start(const std::string& name, const RECT& r)
{
	UI::Start(name, r);
}

void Text::Update(float dt)
{
	UI::Update(dt);
}

void Text::Draw(HDC hdc)
{
	UI::Draw(hdc);

	RECT r = _r;

	int h = r.bottom - r.top;
	int w = r.right - r.left;

	HFONT hFont = CreateFontA(h / _name.size(), w / _maxWidth * kAsciiRatio, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "¸¼Àº °íµñ");	// VARIABLE_PITCH | FF_ROMAN
	HFONT OldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, textColor);
	SetBkColor(hdc, bkColor);

	if (isTransparency)
	{
		SetBkMode(hdc, TRANSPARENT);
	}
	else
	{
		HBRUSH brush = CreateSolidBrush(bkColor);
		SelectObject(hdc, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, bkColor);
		SelectObject(hdc, pen);

		Rectangle(hdc, r.left, r.top, r.right, r.bottom);

		DeleteObject(brush);
		DeleteObject(pen);
	}

	int count = 0;
	int oldTop = r.top;
	for (int i = 0; i < _name.size(); ++i)
	{
		r.top = oldTop + count;
		DrawTextA(hdc, _name[i].data(), _name[i].size(), &r, DT_CENTER | DT_TOP | DT_WORDBREAK);

		SIZE s = {};
		GetTextExtentPointA(hdc, _name[i].data(), _name[i].size(), &s);
		count += s.cy;
	}

	SelectObject(hdc, OldFont);
	DeleteObject(hFont);

	if (isTransparency)
		SetBkMode(hdc, OPAQUE);
}

void Text::SetColor(COLORREF textColor, COLORREF bkColor, bool isTransparency)
{
	this->textColor = textColor;
	this->bkColor = bkColor;
	this->isTransparency = isTransparency;
}
