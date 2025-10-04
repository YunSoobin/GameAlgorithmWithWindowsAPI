#pragma once

#include "FastText.h"

enum class BUTTON_STATE :int
{
	HOVERED = 0,
	FOCUSED,
	CLICKED,
};

class Button : public FastText
{
public:
	virtual void Start(const std::string& name, const RECT& r);
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

	void SetButtonColor(COLORREF textColor, COLORREF hoverColor, COLORREF focusColor, COLORREF clickColor);
	void SetCallbackFunction(const std::function<void()>& func);

private:
	std::function<void()> _callbackFunc = {};
	COLORREF _hoverColor, _focusColor, _clickColor;
	BUTTON_STATE _state = BUTTON_STATE::HOVERED;
};

