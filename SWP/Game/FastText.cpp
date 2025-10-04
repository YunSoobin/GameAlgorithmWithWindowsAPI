#include "stdafx.h"
#include "FastText.h"

void FastText::Start(const std::string& name, const RECT& r)
{
	UI::Start(name, r);
}

void FastText::Update(float dt)
{
}

void FastText::Draw(HDC hdc)
{
	RECT r = _r;
	
	int h = r.bottom - r.top;
	int w = r.right - r.left;

	HFONT hFont = CreateFontA((int)_fontSize.y, (int)_fontSize.x, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "¸¼Àº °íµñ"); // VARIABLE_PITCH | FF_ROMAN
	HFONT OldFont = (HFONT)SelectObject(hdc, hFont);

	SetTextColor(hdc, _textColor);
	SetBkColor(hdc, _bkColor);

	if (_isTransparency)
	{
		SetBkMode(hdc, TRANSPARENT);
	}
	else 
	{
		HBRUSH brush = CreateSolidBrush(_bkColor);
		SelectObject(hdc, brush);
		HPEN pen = CreatePen(PS_SOLID, 1, _bkColor);
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

	if (_isTransparency)
		SetBkMode(hdc, OPAQUE);
}

void FastText::SetName(const std::string& name)
{
	_name.clear();
	_name.push_back(name);
}

void FastText::SetRect(const RECT& r)
{
	_r = r;
}

void FastText::SetSize(const Vector2f& size)
{
	_fontSize = size;
}

void FastText::SetColor(COLORREF textColor, COLORREF bkColor, bool isTransparency)
{
	this->_textColor = textColor;
	this->_bkColor = bkColor;
	this->_isTransparency = isTransparency;
}
