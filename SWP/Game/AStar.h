#pragma once

enum class TILE_TYPE : int
{
	SPACE = 0,
	WALL,
	PATH,	// DEBUG 용
};

enum class SEARCH_MODE : int
{
	DEPTH_FIRST,
	BREADTH_FIRST,
};

struct HeuristicNode
{
	int f, g, h;
	POINT parent;
};

struct CostNode
{
	int x, y;
	int cost;

	bool operator<(const CostNode& s) const
	{
		return this->cost > s.cost;
	}
};

class AStar
{
public:
	void Reset(const SIZE& cellCount);
	void Search(const POINT& beginPoint, const POINT& endPoint);

	void MakeWall(const POINT& pt);
	void MakePath(const POINT& pt);
	void SearchMode(SEARCH_MODE searchMode);

	SIZE Count() const { return _count; }
	std::vector<POINT> GetHistory() const { return _history; }
	TILE_TYPE GetTile(int x, int y) const { return _map[y][x]; }

	// 디버그 용
	void ClearPath();

private:
	bool WithinScope(const POINT& pt);
	bool CheckSpace(const POINT& pt);
	bool CheckWall(const POINT& pt);
	bool Equal(const POINT& pt1, const POINT& pt2);
	int CalculateDistance(const POINT& pt1, const POINT& pt2);
	void MakeHistory(std::vector<std::vector<HeuristicNode>>& heuristicNode, const POINT& endPoint);

private:
	int kDx[4] = { 0, 0, 1, -1 };
	int kDy[4] = { -1, 1, 0, 0 };

private:
	std::vector<std::vector<TILE_TYPE>> _map;
	std::vector<POINT> _history;
	SEARCH_MODE _searchMode = SEARCH_MODE::BREADTH_FIRST;
	SIZE _count;
};

