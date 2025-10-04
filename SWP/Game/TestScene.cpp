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

	_button->Start("Test Btn", { 400, 400, 500, 500 });
	DYNCAST(Button, _button)->SetButtonColor(COLOR_WHITE, COLOR_GRAY, COLOR_DKGRAY, COLOR_BLACK);
	DYNCAST(Button, _button)->SetSize({ 10, 100 });
	DYNCAST(Button, _button)->SetCallbackFunction([&, this]() -> void
		{
			static int count = 0;
			std::string info = "Click Count\n > " + std::to_string(count);

			_text->SetName(info);
			count++;
		});
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

	UI* ptr[] = { _text.get(), _fastText.get(), _button.get() };
	for (int i = 0; i < _countof(ptr); ++i)
		ptr[i]->Update(dt);

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
	UI* ptr[] = { _text.get(), _fastText.get(), _button.get() };
	for (int i = 0; i < _countof(ptr); ++i)
		ptr[i]->Draw(hdc);
}
 