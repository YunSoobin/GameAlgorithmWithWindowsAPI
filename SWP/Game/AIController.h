#pragma once

#include "AStar.h"

constexpr int kAiSegmentCount = (100);

enum class AI_STATE : int
{
	DEAD,
	LIVE,
};

struct AISegment
{
	// AI의 상태
	Vector2f position, realPos;
	AI_STATE state;
	float speed;
	float currTime;

	// AI의 이동경로
	std::vector<POINT> history;
	int nextIdx;
};

class AIController
{
public:
	void Reset(const POINT& targetPoint, const Vector2f& cellSize, const SIZE& cellCount);
	void Update(float dt);

	void Spawn(const POINT& spawnPoint, float moveSpeed);
	void Refresh();

	std::vector<Vector2f> GetUnits();

private:
	Vector2f PointToVector2f(const POINT& pt);
	
public:
	AStar pathFinder;

private:
	AISegment _segment[kAiSegmentCount] = {};
	std::queue<int> _idxBuffer;

	Vector2f _cellSize;
	SIZE _cellCount;
	POINT _target;
};

