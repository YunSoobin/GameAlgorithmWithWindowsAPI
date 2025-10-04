#include "stdafx.h"

#include "Timer.h"
#include "Input.h"
#include "Sound.h"
#include "Camera.h"

#include "Text.h"
#include "FastText.h"

#pragma comment(linker,"/entry:WinMainCRTStartup /subsystem:console")

int kRealResolutionX = 0;
int kRealResolutionY = 0;
TImer kTimer = {};
Input kInput = {};
Sound kSound = {};
Camera kCamera = {};

std::unique_ptr<UI> kText = std::make_unique<Text>();
std::unique_ptr<UI> kFastText = std::make_unique<FastText>();

void Initialize(HWND hwnd)
{
	RECT r = {};
	GetClientRect(hwnd, &r);

	kRealResolutionX = r.right - r.left;
	kRealResolutionY = r.bottom - r.top;

	kText->Start("Hello\nWorld\nPractical\nGame\nProgramming@@@", { 0, 0, 200, 100 });
	DYNCAST(Text, kText)->SetColor(COLOR_BLACK, COLOR_YELLOW, false);
	kFastText->Start("", { 0, 100, 200, 120 });
	DYNCAST(FastText, kFastText)->SetColor(COLOR_WHITE, COLOR_BLUE, false);
	DYNCAST(FastText, kFastText)->SetSize({ 5, 20 });

	kSound.RegisterSound("t1Sound", "test.mp3");
	kCamera.Reset(kRealResolutionX, kRealResolutionY);

	kTimer.Reset();
}

void Update(HWND hwnd)
{
	kTimer.Tick();
	const float dt = kTimer.DeltaTime();

	// TODO
	kInput.Update();
	kCamera.Update(dt);

	constexpr float camSpeed = 100.0F;
	if (kInput.GetKeyPressed(KEYCODE_W))
	{
		kCamera.camPos += {0.0F, -camSpeed * dt};
	}
	if (kInput.GetKeyPressed(KEYCODE_S))
	{
		kCamera.camPos += {0.0F, camSpeed* dt};
	}
	if (kInput.GetKeyPressed(KEYCODE_A))
	{
		kCamera.camPos += {-camSpeed * dt, 0.0F };
	}
	if (kInput.GetKeyPressed(KEYCODE_D))
	{
		kCamera.camPos += {camSpeed* dt, 0.0F};
	}
	if (kInput.GetKeyPressed(KEYCODE_SPACE))
	{
		kCamera.Shake(8.0F, 0.5F);
	}

	std::string alertPosition = "카메라 위치: (" + std::to_string(kCamera.camPos.x) + ", " + std::to_string(kCamera.camPos.y) + ")";
	DYNCAST(FastText, kFastText)->SetName(alertPosition);
}

void Draw(HDC hdc)
{
	// TODO
	HBRUSH whiteBrush = CreateSolidBrush(COLOR_WHITE);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, whiteBrush);
	HPEN whitePen = CreatePen(PS_SOLID, 1, COLOR_WHITE);
	HPEN oldPen = (HPEN)SelectObject(hdc, whitePen);

	Rectangle(hdc, 0, 0, kRealResolutionX, kRealResolutionY);

	{
		HBRUSH objBrush = CreateSolidBrush(COLOR_GREEN);
		SelectObject(hdc, objBrush);
		HPEN objPen = CreatePen(PS_SOLID, 1, COLOR_GREEN);
		SelectObject(hdc, objPen);

		Vector2f camRatio = kCamera.GetCamRatio();
		Ellipse(hdc, 0 + camRatio.x, 0 + camRatio.y, 100 + camRatio.x, 100 + camRatio.y);

		DeleteObject(objBrush);
		DeleteObject(objPen);
	}


	kText->Draw(hdc);
	kFastText->Draw(hdc);

	SelectObject(hdc, oldBrush);
	SelectObject(hdc, oldPen);
	DeleteObject(whiteBrush);
	DeleteObject(whitePen);
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
	case WM_LBUTTONDOWN:
		kInput.SetMouseDown(MOUSECODE_L);
		break;
	case WM_LBUTTONUP:
		kInput.SetMouseUp(MOUSECODE_L);
		break;
	case WM_RBUTTONDOWN:
		kInput.SetMouseDown(MOUSECODE_R);
		break;
	case WM_RBUTTONUP:
		kInput.SetMouseUp(MOUSECODE_R);
		break;
	case WM_MBUTTONDOWN:
		kInput.SetMouseDown(MOUSECODE_M);
		break;
	case WM_MBUTTONUP:
		kInput.SetMouseUp(MOUSECODE_M);
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