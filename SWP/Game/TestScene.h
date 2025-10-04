#pragma once

#include "Scene.h"

#include "Text.h"
#include "FastText.h"

class TestScene : public Scene
{
public:
	virtual void Start();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);

private:
	std::unique_ptr<UI> _text = std::make_unique<Text>();
	std::unique_ptr<UI> _fastText = std::make_unique<FastText>();
};

