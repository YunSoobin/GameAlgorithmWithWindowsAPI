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