#pragma once

#include "Scene.h"

#include "Text.h"
#include "FastText.h"
#include "Button.h"
#include "HpBar.h"
#include "GaugeBar.h"

#include "LaserObject.h"
#include "RotationObject.h"

#include "AStar.h"

class TestScene : public Scene
{
public:
	virtual void Start();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

private:
	std::unique_ptr<UI> _camPosText = std::make_unique<FastText>();
	std::unique_ptr<UI> _button1 = std::make_unique<Button>();
	std::unique_ptr<UI> _button2 = std::make_unique<Button>();

	AStar _pathFinder = {};
};

