#include "stdafx.h"
#include "AStar.h"

void AStar::Reset(const SIZE& cellCount)
{
	_map.clear();
	_map = std::vector<std::vector<TILE_TYPE>>(cellCount.cy, std::vector<TILE_TYPE>(cellCount.cx, TILE_TYPE::SPACE));
	_count = cellCount;
}

void AStar::Search(const POINT& beginPoint, const POINT& endPoint)
{
	if (!WithinScope(beginPoint) || !WithinScope(endPoint) || CheckWall(beginPoint) || CheckWall(endPoint) || Equal(beginPoint, endPoint))
		return;

	std::vector<std::vector<bool>> closedList(_count.cy, std::vector<bool>(_count.cx, false));
	std::vector<std::vector<HeuristicNode>> heuristicNode(_count.cy, std::vector<HeuristicNode>(_count.cx));

	for (int i = 0; i < _count.cy; ++i)
	{
		for (int j = 0; j < _count.cx; ++j)
		{
			heuristicNode[i][j].f = heuristicNode[i][j].g = heuristicNode[i][j].h = std::numeric_limits<int>().infinity();
			heuristicNode[i][j].parent = { -1, -1 };
			closedList[i][j] = false;
		}
	}

	heuristicNode[beginPoint.y][beginPoint.x].f = heuristicNode[beginPoint.y][beginPoint.x].g = heuristicNode[beginPoint.y][beginPoint.x].h = 0;
	heuristicNode[beginPoint.y][beginPoint.x].parent = { beginPoint.x, beginPoint.y };

	std::priority_queue<CostNode> openList = {};
	openList.push({ beginPoint.x, beginPoint.y, 0 });

	while (!openList.empty())
	{
		CostNode curr = openList.top();
		openList.pop();

		closedList[curr.y][curr.x] = true;

		int nextf, nextg, nexth;

		for (std::size_t i = 0; i < 4; ++i)
		{
			POINT next = { curr.x + kDx[i], curr.y + kDy[i] };

			if (WithinScope(next))
			{
				if (Equal(next, endPoint))
				{
					heuristicNode[next.y][next.x].parent = { curr.x, curr.y };
					MakeHistory(heuristicNode, endPoint);
					return;
				}
				else if (!closedList[next.y][next.x] && CheckSpace(next))
				{
					nextg = (_searchMode == SEARCH_MODE::BREADTH_FIRST ? heuristicNode[curr.y][curr.x].g : 0) + 10;
					nexth = CalculateDistance(next, endPoint);
					nextf = nextg + nexth;

					if (heuristicNode[next.y][next.x].f == std::numeric_limits<int>().infinity() || heuristicNode[next.y][next.x].f > nextf)
					{
						heuristicNode[next.y][next.x].g = nextg;
						heuristicNode[next.y][next.x].h = nexth;
						heuristicNode[next.y][next.x].f = nextf;

						heuristicNode[next.y][next.x].parent = { curr.x, curr.y };

						openList.push({ next.x, next.y, nextf });
					}
				}
			}
		}
	}
}

void AStar::MakeWall(const POINT& pt)
{
	_map[pt.y][pt.x] = TILE_TYPE::WALL;
}

void AStar::MakePath(const POINT& pt)
{
	_map[pt.y][pt.x] = TILE_TYPE::PATH;
}

void AStar::SearchMode(SEARCH_MODE searchMode)
{
	_searchMode = searchMode;
}

void AStar::ClearPath()
{
	for (int i = 0; i < _count.cy; ++i)
	{
		for (int j = 0; j < _count.cx; ++j)
		{
			if (_map[i][j] == TILE_TYPE::PATH)
			{
				_map[i][j] = TILE_TYPE::SPACE;
			}
		}
	}
}

bool AStar::WithinScope(const POINT& pt)
{
	return (0 <= pt.x && pt.x < _count.cx && 0 <= pt.y && pt.y < _count.cy);
}

bool AStar::CheckSpace(const POINT& pt)
{
	return (_map[pt.y][pt.x] == TILE_TYPE::SPACE);
}

bool AStar::CheckWall(const POINT& pt)
{
	return (_map[pt.y][pt.x] == TILE_TYPE::WALL);
}

bool AStar::Equal(const POINT& pt1, const POINT& pt2)
{
	return (pt1.x == pt2.x && pt1.y == pt2.y);
}

int AStar::CalculateDistance(const POINT& pt1, const POINT& pt2)
{
	POINT diff = { std::abs(pt1.x - pt2.x), std::abs(pt1.y - pt2.y) };
	int min = min(diff.x, diff.y);
	diff = { diff.x - min, diff.y - min };

	return min * 14 + (diff.x + diff.y) * 10;
}

void AStar::MakeHistory(std::vector<std::vector<HeuristicNode>>& heuristicNode, const POINT& endPoint)
{
	_history.clear();
	POINT current = endPoint;
	_history.push_back(current);

	while (!(heuristicNode[current.y][current.x].parent.x == current.x && heuristicNode[current.y][current.x].parent.y == current.y))
	{
		POINT temp = heuristicNode[current.y][current.x].parent;

		current.x = temp.x;
		current.y = temp.y;
		
		_history.push_back(current);
	}

	// _history.pop_back();	// (시작위치는 지우기)
	std::reverse(_history.begin(), _history.end());
}
