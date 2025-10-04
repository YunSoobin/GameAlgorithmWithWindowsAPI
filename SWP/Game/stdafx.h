#pragma once
#pragma comment(lib, "winmm")

#include <windows.h>
#include <tchar.h>

#include <mmsystem.h>
#include <Digitalv.h>

#include <iostream>
#include <random>
#include <vector>
#include <string>
#include <map>
#include <functional>

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
	COLOR_GRAY = RGB(180, 180, 180),
	COLOR_DKGRAY = RGB(80, 80, 80),
	COLOR_RED = RGB(255, 0, 0),
	COLOR_GREEN = RGB(0, 255, 0),
	COLOR_BLUE = RGB(0, 0, 255),
	COLOR_YELLOW= RGB(255, 255, 0),
	COLOR_MAGENTA= RGB(255, 0, 255),
	COLOR_CYAN = RGB(0, 255, 255),
};

struct Vector2f
{
	float x, y;

	Vector2f& operator+=(const Vector2f& other);
};

float GetRandomValuef(float min, float max);
float LinearInterpolation(float a, float b, float t);

bool AABB(const RECT& a, const RECT& b);
bool BoxAndPoint(const RECT& box, const Vector2f& p);