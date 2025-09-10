#include "stdafx.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int kRealResolutionX = 0;
int kRealResolutionY = 0;

void Initialize(HWND hwnd)
{
	RECT r = {};
	GetClientRect(hwnd, &r);

	kRealResolutionX = r.right - r.left;
	kRealResolutionY = r.bottom - r.top;
}

void Draw(HDC hdc)
{
	HPEN pen = CreatePen(PS_SOLID, 10, RGB(255, 0, 0));
	HBRUSH oldPen = (HBRUSH)SelectObject(hdc, pen);
	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, brush);

	Rectangle(hdc, 0, 0, 100, 100);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	DeleteObject(pen);
	DeleteObject(brush);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT	ps;
	HDC hDC;

	switch (msg)
	{
	case WM_CREATE:
		Initialize(hwnd);
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		Draw(hDC);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	LPCTSTR lpszClass = L"Win32 Practical Game Programming";

	WNDCLASSEX wndClass = {};
	wndClass.cbSize = sizeof(wndClass);
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hInstance = hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = lpszClass;
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.lpfnWndProc = (WNDPROC)WndProc;

	RegisterClassEx(&wndClass);

	HWND hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);	// WM_PAINT

	MSG msg = {};
	for (;;)
	{
		if (GetMessage(&msg, 0, 0, 0))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if (msg.message == WM_QUIT)
		{
			break;
		}
	}

	return (int)msg.wParam;
}