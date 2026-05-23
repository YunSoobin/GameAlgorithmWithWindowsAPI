#include "stdafx.h"
#include "Input.h"

void Input::Update()
{
	// 키보드
	BYTE keyState[256] = {};
	GetKeyboardState(keyState);

	for (int i = 0; i < 256; ++i)
	{
		if (keyState[i] <= 1 && _preKeyChar[i] <= 1)
			_currKeyState[i] = KEYSTATE::KEY_NONE;
		else if (keyState[i] <= 1 && _preKeyChar[i] >= 128)
			_currKeyState[i] = KEYSTATE::KEY_UP;
		else if (keyState[i] >= 128 && _preKeyChar[i] >= 128)
			_currKeyState[i] = KEYSTATE::KEY_PRESSED;
		else if (keyState[i] >= 128 && _preKeyChar[i] <= 1)
			_currKeyState[i] = KEYSTATE::KEY_DOWN;
	}

	memcpy(&_preKeyChar, &keyState, 256);

	// 마우스
	for (int i = 0; i < 3; ++i)
	{
		if (_prevMouseState[i] == KEYSTATE::KEY_NONE && _currMouseState[i] == KEYSTATE::KEY_DOWN)
		{
			_prevMouseState[i] = KEYSTATE::KEY_DOWN;
		}
		else if (_prevMouseState[i] == KEYSTATE::KEY_DOWN && _currMouseState[i] == KEYSTATE::KEY_DOWN)
		{
			_prevMouseState[i] = KEYSTATE::KEY_PRESSED;
		}
		else if (_prevMouseState[i] == KEYSTATE::KEY_PRESSED && _currMouseState[i] == KEYSTATE::KEY_UP)
		{
			_prevMouseState[i] = KEYSTATE::KEY_UP;
		}
		else if (_prevMouseState[i] == KEYSTATE::KEY_UP && _currMouseState[i] == KEYSTATE::KEY_UP)
		{
			_prevMouseState[i] = KEYSTATE::KEY_NONE;
		}
	}
}

void Input::SetMousePosition(int x, int y)
{
	_pos = { x, y };
}
