#pragma once

#include "Sound.h"
#include "Input.h"
#include "Timer.h"
#include "Camera.h"

enum class OBJECT_SHAPE : int
{
	CIRCLE,
	RECTANGLE,
	TRIANGLE,
};

class Object
{
public:
	virtual void Start() {}
	virtual void Update(float dt) {}
	virtual void Draw(HDC hdc) {}

public:
	Vector2f position = {};
	Vector2f size = {};	// half size
};

