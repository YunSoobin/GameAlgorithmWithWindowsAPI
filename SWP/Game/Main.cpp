#include "stdafx.h"

#include "Timer.h"

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

int kRealResolutionX = 0;
int kRealResolutionY = 0;
TImer kTImer = {};

void Initialize(HWND hwnd)
{
	RECT r = {};
	GetClientRect(hwnd, &r);

	kRealResolutionX = r.right - r.left;
	kRealResolutionY = r.bottom - r.top;

	kTImer.Reset();
}

void Update(HWND hwnd)
{
	kTImer.Tick();
	const float deltaTime = kTImer.DeltaTime();

	// TODO

}

void Draw(HDC hdc)
{
	// TODO
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 255, 255));
	HPEN oldPen = (HPEN)SelectObject(hdc, newPen);
	HBRUSH newBrush = CreateSolidBrush(RGB(0, 255, 255));
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, newBrush);

	Rectangle(hdc, 0, 0, kRealResolutionX, kRealResolutionY);

	HFONT newFont = CreateFont(50, 20, 0, 0, 0, TRUE, FALSE, FALSE, HANGUL_CHARSET, 0, 0, 0, 0, _TEXT("Arial"));
	HFONT oldFont = (HFONT)SelectObject(hdc, newFont);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(0, 0, 255));
	SetBkColor(hdc, RGB(255, 255, 255));
	//SetBkMode(hdc, OPAQUE);

	RECT r = { 0, 0, 1000, 400 };
	const char* str = "Practical Game Programming";
	//TextOutA(hdc, 0, 0, str, strlen(str));
	DrawTextA(hdc, str, strlen(str), &r, DT_LEFT | DT_TOP);

	SelectObject(hdc, oldPen);
	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldFont);
	DeleteObject(newPen);
	DeleteObject(newBrush);
	DeleteObject(newFont);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT	ps;
	HDC hDC, mDC;	// hDC(프론트버퍼에 해당), mDC(백버퍼에 해당)
	HBITMAP hBitmap;

	switch (msg)
	{
	case WM_CREATE:
		SetTimer(hwnd, 0, 1, 0);	// ID가 0인 타이머
		Initialize(hwnd);
		break;
	case WM_TIMER:
		Update(hwnd);
		InvalidateRect(hwnd, 0, 0);	// WM_PAINT메세지를 호출
		break;
	case WM_PAINT:
		hDC = BeginPaint(hwnd, &ps);
		mDC = CreateCompatibleDC(hDC);
		hBitmap = CreateCompatibleBitmap(hDC, kRealResolutionX, kRealResolutionY);
		SelectObject(mDC, hBitmap);
		Draw(mDC);
		BitBlt(hDC, 0, 0, kRealResolutionX, kRealResolutionY, mDC, 0, 0, SRCCOPY);
		DeleteDC(mDC);
		DeleteObject(hBitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hwnd, 0);	// ID가 0인 타이머
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