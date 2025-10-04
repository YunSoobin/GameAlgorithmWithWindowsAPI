#include "stdafx.h"
#include "Button.h"

void Button::Start(const std::string& name, const RECT& r)
{
	_name.clear();
	_name.push_back(name);

	_r = r;
}

void Button::Update(float dt)
{
	FastText::Update(dt);

	POINT pt = Input::Handler().GetMousePosition();
	bool overlap = BoxAndPoint(_r, { (float)pt.x, (float)pt.y });

	if (_state != BUTTON_STATE::CLICKED)
	{
		if (overlap)
			_state = BUTTON_STATE::FOCUSED;
		else
			_state = BUTTON_STATE::HOVERED;
	}

	if (Input::Handler().GetMouseDown(MOUSECODE_L) && _state == BUTTON_STATE::FOCUSED)
	{
		_state = BUTTON_STATE::CLICKED;
	}
	else if (Input::Handler().GetMouseUp(MOUSECODE_L) && _state == BUTTON_STATE::CLICKED)
	{
		if (_callbackFunc)
			_callbackFunc();
		
		if (overlap)
			_state = BUTTON_STATE::FOCUSED;
		else
			_state = BUTTON_STATE::HOVERED;
	}
}

void Button::Draw(HDC hdc)
{
	HBRUSH brush;
	HPEN pen;

	if (_state == BUTTON_STATE::FOCUSED)
	{
		brush = CreateSolidBrush(_focusColor);
		pen = CreatePen(PS_SOLID, 1, _focusColor);
	}
	else if (_state == BUTTON_STATE::HOVERED)
	{
		brush = CreateSolidBrush(_hoverColor);
		pen = CreatePen(PS_SOLID, 1, _hoverColor);
	}
	else
	{
		brush = CreateSolidBrush(_clickColor);
		pen = CreatePen(PS_SOLID, 1, _clickColor);
	}

	SelectObject(hdc, brush);
	SelectObject(hdc, pen);

	Rectangle(hdc, _r.left, _r.top, _r.right, _r.bottom);

	DeleteObject(brush);
	DeleteObject(pen);

	FastText::Draw(hdc);
}

void Button::SetButtonColor(COLORREF textColor, COLORREF hoverColor, COLORREF focusColor, COLORREF clickColor)
{
	_hoverColor = hoverColor;
	_focusColor = focusColor;
	_clickColor = clickColor;

	FastText::SetColor(textColor, 0, true);
}

void Button::SetCallbackFunction(const std::function<void()>& func)
{
	_callbackFunc = func;
}
