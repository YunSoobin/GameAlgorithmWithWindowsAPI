#include "stdafx.h"
#include "TestScene.h"

void TestScene::Start()
{
	Scene::Start();

	Sound::Handler().RegisterSound("t1Sound", "test.mp3");

	_text->Start("Hello\nWorld\nPractical\nGame\nProgramming@@@", { 0, 0, 200, 100 });
	DYNCAST(Text, _text)->SetColor(COLOR_BLACK, COLOR_YELLOW, false);
	_fastText->Start("", { 0, 100, 200, 120 });
	DYNCAST(FastText, _fastText)->SetColor(COLOR_WHITE, COLOR_BLUE, false);
	DYNCAST(FastText, _fastText)->SetSize({ 5, 20 });
}

void TestScene::Update(float dt)
{
	Scene::Update(dt);

	constexpr float camSpeed = 100.0F;
	if (Input::Handler().GetKeyPressed(KEYCODE_W))
	{
		Camera::Handler().camPos += {0.0F, -camSpeed * dt};
	}
	if (Input::Handler().GetKeyPressed(KEYCODE_S))
	{
		Camera::Handler().camPos += {0.0F, camSpeed* dt};
	}
	if (Input::Handler().GetKeyPressed(KEYCODE_A))
	{
		Camera::Handler().camPos += {-camSpeed * dt, 0.0F };
	}
	if (Input::Handler().GetKeyPressed(KEYCODE_D))
	{
		Camera::Handler().camPos += {camSpeed* dt, 0.0F};
	}
	if (Input::Handler().GetKeyPressed(KEYCODE_SPACE))
	{
		Camera::Handler().Shake(8.0F, 0.5F);
	}

	std::string alertPosition = "카메라 위치: (" + std::to_string(Camera::Handler().camPos.x) + ", " + std::to_string(Camera::Handler().camPos.y) + ")";
	DYNCAST(FastText, _fastText)->SetName(alertPosition);
}

void TestScene::Draw(HDC hdc)
{
	Scene::Draw(hdc);

	// 오브젝트 그리기
	HBRUSH objBrush = CreateSolidBrush(COLOR_GREEN);
	SelectObject(hdc, objBrush);
	HPEN objPen = CreatePen(PS_SOLID, 1, COLOR_GREEN);
	SelectObject(hdc, objPen);

	Vector2f camRatio = Camera::Handler().GetCamRatio();
	Ellipse(hdc, 0 + camRatio.x, 0 + camRatio.y, 100 + camRatio.x, 100 + camRatio.y);

	DeleteObject(objBrush);
	DeleteObject(objPen);

	// UI 그리기
	_text->Draw(hdc);
	_fastText->Draw(hdc);
}
