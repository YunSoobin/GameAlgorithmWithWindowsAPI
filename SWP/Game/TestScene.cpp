#include "stdafx.h"
#include "TestScene.h"

void TestScene::Start()
{
	Scene::Start();

	Sound::Handler().RegisterSound("t1Sound", "test.mp3");

	// UI
	_camPosText->Start("", { 0, 0, 200, 20 });
	DYNCAST(FastText, _camPosText)->SetColor(COLOR_WHITE, COLOR_BLUE, false);
	DYNCAST(FastText, _camPosText)->SetSize({ 5, 20 });

	_button->Start("Reset", { 0, 20, 200, 50 });
	DYNCAST(Button, _button)->SetButtonColor(COLOR_WHITE, COLOR_GRAY, COLOR_DKGRAY, COLOR_BLACK);
	DYNCAST(Button, _button)->SetSize({ 10, 30 });
	DYNCAST(Button, _button)->SetCallbackFunction([&, this]() -> void { _aiController.Reset({ 9, 9 }, { 100, 100 }, { 10, 10 }); });
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

	// Make Wall
	{
		Vector2f ratio = Camera::Handler().GetCamRatio();
		SIZE size = _aiController.pathFinder.Count();

		if (Input::Handler().GetMouseDown(MOUSECODE_L))
		{
			for (int i = 0; i < size.cy; ++i)
			{
				for (int j = 0; j < size.cx; ++j)
				{
					RECT r = { (j + 0) * 100 + ratio.x, (i + 0) * 100 + ratio.y, (j + 1) * 100 + ratio.x, (i + 1) * 100 + ratio.y };
					if (BoxAndPoint(r, { (float)Input::Handler().GetMousePosition().x, (float)Input::Handler().GetMousePosition().y }))
					{
						_aiController.pathFinder.MakeWall({ j , i });
						_aiController.Refresh();
					}
				}
			}
		}
		else if (Input::Handler().GetMouseDown(MOUSECODE_R))
		{
			for (int i = 0; i < size.cy; ++i)
			{
				for (int j = 0; j < size.cx; ++j)
				{
					RECT r = { (j + 0) * 100 + ratio.x, (i + 0) * 100 + ratio.y, (j + 1) * 100 + ratio.x, (i + 1) * 100 + ratio.y };
					if (BoxAndPoint(r, { (float)Input::Handler().GetMousePosition().x, (float)Input::Handler().GetMousePosition().y }))
					{
						_aiController.Spawn({ j, i }, 3.0F);
					}
				}
			}
		}
	}

	_aiController.Update(dt);

	// UI
	UI* ptr[] = { _camPosText.get(), _button.get() };
	for (int i = 0; i < _countof(ptr); ++i)
		ptr[i]->Update(dt);

	std::string alertPosition = "카메라 위치: (" + std::to_string(Camera::Handler().camPos.x) + ", " + std::to_string(Camera::Handler().camPos.y) + ")";
	DYNCAST(FastText, _camPosText)->SetName(alertPosition);
}

void TestScene::Draw(HDC hdc)
{
	Scene::Draw(hdc);

	HPEN pen = CreatePen(PS_SOLID, 3, 0);
	HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
	HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
	HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH objBrush = CreateSolidBrush(RGB(52, 15, 62));
	SelectObject(hdc, pen);

	Vector2f ratio = Camera::Handler().GetCamRatio();
	SIZE size = _aiController.pathFinder.Count();

	for (int i = 0; i < size.cy; ++i)
	{
		for (int j = 0; j < size.cx; ++j)
		{
			if (_aiController.pathFinder.GetTile(j, i) == TILE_TYPE::SPACE)
				SelectObject(hdc, greenBrush);
			else if (_aiController.pathFinder.GetTile(j, i) == TILE_TYPE::WALL)
				SelectObject(hdc, redBrush);
			else
				SelectObject(hdc, blueBrush);

			Rectangle(hdc, (j + 0) * 100 + ratio.x, (i + 0) * 100 + ratio.y, (j + 1) * 100 + ratio.x, (i + 1) * 100 + ratio.y);
		}
	}

	SelectObject(hdc, objBrush);
	auto units = _aiController.GetUnits();
	for (auto const& i : units)
	{
		Rectangle(hdc, i.x - 50 + ratio.x, i.y - 50 + ratio.y, i.x + 50 + ratio.x, i.y + 50 + ratio.y);
	}

	DeleteObject(pen);
	DeleteObject(greenBrush);
	DeleteObject(redBrush);
	DeleteObject(blueBrush);
	DeleteObject(objBrush);

	// UI 그리기
	UI* ptr[] = { _camPosText.get(), _button.get() };
	for (int i = 0; i < _countof(ptr); ++i)
		ptr[i]->Draw(hdc);
}
 