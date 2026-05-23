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

	_button1->Start("Reset", { 0, 20, 200, 50 });
	DYNCAST(Button, _button1)->SetButtonColor(COLOR_WHITE, COLOR_GRAY, COLOR_DKGRAY, COLOR_BLACK);
	DYNCAST(Button, _button1)->SetSize({ 10, 30 });
	DYNCAST(Button, _button1)->SetCallbackFunction([&, this]() -> void { _pathFinder.Reset({ 8, 8 }); _pathFinder.SearchMode(SEARCH_MODE::DEPTH_FIRST); });

	_button2->Start("Find Path", { 0, 50, 200, 80 });
	DYNCAST(Button, _button2)->SetButtonColor(COLOR_WHITE, COLOR_GRAY, COLOR_DKGRAY, COLOR_BLACK);
	DYNCAST(Button, _button2)->SetSize({ 10, 30 });
	DYNCAST(Button, _button2)->SetCallbackFunction([&, this]() -> void
		{
			_pathFinder.ClearPath();
			_pathFinder.Search({ 0, 0 }, { 7, 7 });
			auto history = _pathFinder.GetHistory();

			for (int i = 0; i < history.size(); ++i)
			{
				_pathFinder.MakePath({ history[i].x, history[i].y });
			}
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

	// Make Wall
	{
		Vector2f ratio = Camera::Handler().GetCamRatio();
		SIZE size = _pathFinder.Count();

		if (Input::Handler().GetMouseDown(MOUSECODE_L))
		{
			for (int i = 0; i < size.cy; ++i)
			{
				for (int j = 0; j < size.cx; ++j)
				{
					RECT r = { (j + 0) * 100 + ratio.x, (i + 0) * 100 + ratio.y, (j + 1) * 100 + ratio.x, (i + 1) * 100 + ratio.y };
					if (BoxAndPoint(r, { (float)Input::Handler().GetMousePosition().x, (float)Input::Handler().GetMousePosition().y }))
					{
						_pathFinder.MakeWall({ j, i });
					}
				}
			}
		}
	}

	// UI
	UI* ptr[] = { _camPosText.get(), _button1.get(), _button2.get() };
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
	SelectObject(hdc, pen);

	Vector2f ratio = Camera::Handler().GetCamRatio();
	SIZE size = _pathFinder.Count();

	for (int i = 0; i < size.cy; ++i)
	{
		for (int j = 0; j < size.cx; ++j)
		{
			if (_pathFinder.GetTile(j, i) == TILE_TYPE::SPACE)
				SelectObject(hdc, greenBrush);
			else if (_pathFinder.GetTile(j, i) == TILE_TYPE::WALL)
				SelectObject(hdc, redBrush);
			else
				SelectObject(hdc, blueBrush);

			Rectangle(hdc, (j + 0) * 100 + ratio.x, (i + 0) * 100 + ratio.y, (j + 1) * 100 + ratio.x, (i + 1) * 100 + ratio.y);
		}
	}

	DeleteObject(pen);
	DeleteObject(greenBrush);
	DeleteObject(redBrush);
	DeleteObject(blueBrush);

	// UI 그리기
	UI* ptr[] = { _camPosText.get(), _button1.get(), _button2.get() };
	for (int i = 0; i < _countof(ptr); ++i)
		ptr[i]->Draw(hdc);
}
 