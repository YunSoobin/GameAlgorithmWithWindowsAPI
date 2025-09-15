#pragma once

#include <windows.h>
#include <tchar.h>

#include <iostream>
#include <random>
#include <vector>
#include <string>

#define SCREEN_WIDTH (1280)
#define SCREEN_HEIGHT (920)

#define DEBUG_PRINT(string, ...) { \
char buf[0x200] = ""; \
sprintf_s(buf, string, __VA_ARGS__);	\
OutputDebugStringA(buf); \
} \

#define DEBUG_MSG(string, ...) { \
char buf[0x200] = ""; \
sprintf_s(buf, string, __VA_ARGS__);	\
MessageBoxA(0, buf, "", 0); \
} \

#define DYNCAST(type, ptr) (dynamic_cast<type*>(ptr.get()))

constexpr float kPi = 3.14159265359F;

enum LINEAR_COLOR : int
{
	COLOR_WHITE = RGB(255, 255, 255),
	COLOR_BLACK = RGB(0, 0, 0),
	COLOR_RED = RGB(255, 0, 0),
	COLOR_GREEN = RGB(0, 255, 0),
	COLOR_BLUE = RGB(0, 0, 255),
	COLOR_YELLOW= RGB(255, 255, 0),
	COLOR_MAGENTA= RGB(255, 0, 255),
	COLOR_CYAN = RGB(0, 255, 255),
};