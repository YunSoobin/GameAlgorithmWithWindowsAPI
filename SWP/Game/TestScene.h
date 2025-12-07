#pragma once

#include "Scene.h"

#include "Text.h"
#include "FastText.h"
#include "Button.h"
#include "HpBar.h"
#include "GaugeBar.h"

#include "LaserObject.h"
#include "RotationObject.h"

class TestScene : public Scene
{
public:
	virtual void Start();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

private:
	std::unique_ptr<UI> _text = std::make_unique<Text>();
	std::unique_ptr<UI> _fastText = std::make_unique<FastText>();
	std::unique_ptr<UI> _button = std::make_unique<Button>();
	std::unique_ptr<UI> _hpBar = std::make_unique<HpBar>();
	std::unique_ptr<UI> _gaugeBar = std::make_unique<GaugeBar>();

	std::unique_ptr<Object> _laser = std::make_unique<LaserObject>();
	std::unique_ptr<Object> _rotation = std::make_unique<RotationObject>();
};

