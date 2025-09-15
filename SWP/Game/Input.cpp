#include "stdafx.h"
#include "Input.h"

void Input::Update()
{
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
}
