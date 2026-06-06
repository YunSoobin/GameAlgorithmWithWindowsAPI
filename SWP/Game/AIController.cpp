#include "stdafx.h"
#include "AIController.h"
#include "Camera.h"

void AIController::Reset(const POINT& targetPoint, const Vector2f& cellSize, const SIZE& cellCount)
{
	_target = targetPoint;
	_cellCount = cellCount;
	_cellSize = cellSize;

	pathFinder.Reset(cellCount);
	pathFinder.SearchMode(SEARCH_MODE::BREADTH_FIRST);

	while (!_idxBuffer.empty())
		_idxBuffer.pop();

	for (int i = 0; i < kAiSegmentCount; ++i)
	{
		_idxBuffer.push(i);
		_segment[i].position = {};
		_segment[i].state = AI_STATE::DEAD;
		_segment[i].history = {};
		_segment[i].nextIdx = 0;
		_segment[i].currTime = 0.0F;
		_segment[i].realPos = {};
	}
}

void AIController::Update(float dt)
{
	for (int i = 0; i < kAiSegmentCount; ++i)
	{
		if (_segment[i].state == AI_STATE::DEAD || _segment[i].history.size() <= 0)
			continue;

		_segment[i].currTime += dt;

		_segment[i].nextIdx = min(_segment[i].nextIdx, _segment[i].history.size() - 1);
		Vector2f nextPos = PointToVector2f(_segment[i].history[_segment[i].nextIdx]);
		float d = _segment[i].currTime / _segment[i].speed;

		float lerpx = LinearInterpolation(_segment[i].position.x, nextPos.x, d);
		float lerpy = LinearInterpolation(_segment[i].position.y, nextPos.y, d);
		_segment[i].realPos = { lerpx, lerpy };

		if (d >= 1.0F)
		{
			_segment[i].nextIdx = (_segment[i].nextIdx + 1);
			_segment[i].position = _segment[i].realPos;
			_segment[i].currTime = 0.0F;

			if (_segment[i].nextIdx == _segment[i].history.size())
			{
				_segment[i].state = AI_STATE::DEAD;
				_idxBuffer.push(i);
			}
		}
	}
}

void AIController::Spawn(const POINT& spawnPoint, float moveSpeed)
{
	if (_idxBuffer.empty())
		return;

	int idx = _idxBuffer.front();
	_idxBuffer.pop();

	_segment[idx].state = AI_STATE::LIVE;
	_segment[idx].position = _segment[idx].realPos = PointToVector2f(spawnPoint);
	_segment[idx].speed = 1.0F / moveSpeed;

	pathFinder.Search(spawnPoint, _target);
	_segment[idx].history = pathFinder.GetHistory();
	_segment[idx].nextIdx = 0;
	_segment[idx].currTime = 0.0F;
}

void AIController::Refresh()
{
	for (int i = 0; i < kAiSegmentCount; ++i)
	{
		if (_segment[i].state == AI_STATE::DEAD)
			continue;

		pathFinder.Search({ (int)(_segment[i].realPos.x / _cellSize.x), (int)(_segment[i].realPos.y / _cellSize.y) }, _target);

		_segment[i].history = pathFinder.GetHistory();
		_segment[i].position = _segment[i].realPos;
		_segment[i].nextIdx = 0;
		_segment[i].currTime = 0.0F;
	}
}

std::vector<Vector2f> AIController::GetUnits()
{
	std::vector<Vector2f> units = {};

	for (int i = 0; i < kAiSegmentCount; ++i)
	{
		if (_segment[i].state == AI_STATE::DEAD)
			continue;

		units.push_back(_segment[i].realPos);
	}

	return units;
}

Vector2f AIController::PointToVector2f(const POINT& pt)
{
	Vector2f flPt = {};
	flPt.x = pt.x * _cellSize.x + (_cellSize.x * 0.5F);
	flPt.y = pt.y * _cellSize.y + (_cellSize.y * 0.5F);

	return flPt;
}
