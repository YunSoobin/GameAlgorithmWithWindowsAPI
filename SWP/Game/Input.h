#pragma once

enum KEYCODE : int
{
	KEYCODE_ALPHA0 = '0',
	KEYCODE_ALPHA1 = '1',
	KEYCODE_ALPHA2 = '2',
	KEYCODE_ALPHA3 = '3',
	KEYCODE_ALPHA4 = '4',
	KEYCODE_ALPHA5 = '5',
	KEYCODE_ALPHA6 = '6',
	KEYCODE_ALPHA7 = '7',
	KEYCODE_ALPHA8 = '8',
	KEYCODE_ALPHA9 = '9',
	
	KEYCODE_D = 'D',
	KEYCODE_W = 'W',
	KEYCODE_S = 'S',
	KEYCODE_A = 'A',
	
	KEYCODE_SPACE = VK_SPACE,

	KEYCODE_DOWN = VK_DOWN,
	KEYCODE_UP = VK_UP,
	KEYCODE_LEFT = VK_LEFT,
	KEYCODE_RIGHT = VK_RIGHT,
	
	KEYCODE_ESC = VK_ESCAPE,
};

enum MOUSECODE : int
{
	MOUSECODE_L,
	MOUSECODE_M,
	MOUSECODE_R,
};

enum class KEYSTATE : int
{
	KEY_NONE,
	KEY_UP,
	KEY_DOWN,
	KEY_PRESSED,
	KEY_COUNT,
};

class Input
{
public:
	static Input& Handler() { static Input g = {}; return g; }

	void Update();

	bool GetKeyDown(int keycode) { return _currKeyState[keycode] == KEYSTATE::KEY_DOWN ? true : false; };
	bool GetKeyUp(int keycode) { return _currKeyState[keycode] == KEYSTATE::KEY_UP ? true : false; };
	bool GetKeyPressed(int keycode) { return _currKeyState[keycode] == KEYSTATE::KEY_PRESSED ? true : false; };

	void SetMouseDown(int keycode) { _currMouseState[keycode] = KEYSTATE::KEY_DOWN; }
	void SetMouseUp(int keycode) { _currMouseState[keycode] = KEYSTATE::KEY_UP; }

	bool GetMouseDown(int keycode) { return _prevMouseState[keycode] == KEYSTATE::KEY_DOWN ? true : false; }
	bool GetMouseUp(int keycode) { return _prevMouseState[keycode] == KEYSTATE::KEY_UP ? true : false; }
	bool GetMousePressed(int keycode) { return _prevMouseState[keycode] == KEYSTATE::KEY_PRESSED ? true : false; }

	POINT GetMousePosition() const { return _pos; }

private:
	unsigned char _preKeyChar[256] = {};
	KEYSTATE _currKeyState[256] = {};

	POINT _pos = {};
	KEYSTATE _prevMouseState[3] = {};
	KEYSTATE _currMouseState[3] = {};
};

