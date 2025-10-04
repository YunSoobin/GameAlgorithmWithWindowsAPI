#pragma once

#include "Sound.h"
#include "Input.h"
#include "Timer.h"
#include "Camera.h"

class Scene
{
public:
	virtual void Start();
	virtual void Update(float dt);
	virtual void Draw(HDC hdc);
};
