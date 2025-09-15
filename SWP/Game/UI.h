#pragma once

#pragma warning(disable:4996)

constexpr float kAsciiRatio = (0.78F);

class UI
{
public:
	virtual void Start(const std::string& name, const RECT& r);
	virtual void Update(float dt) {};
	virtual void Draw(HDC hcd) {};

	void SetName(const std::string& name);
	void SetRect(const RECT& r) { _r = r; }

protected:
	std::vector<std::string> _name;
	RECT _r;

	int _maxWidth;

};

