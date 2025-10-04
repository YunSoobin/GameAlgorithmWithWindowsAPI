#include "stdafx.h"

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
    this->x += other.x;
    this->y += other.y;

    return *this;
}

float GetRandomValuef(float min, float max)
{
    static std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(min, max);

    return dis(gen);
}

float LinearInterpolation(float a, float b, float t)
{
    return (1.0F - t) * a + t * b;
}

bool AABB(const RECT& a, const RECT& b)
{
    if (a.right < b.left || a.left > b.right) return false;
    if (a.bottom < b.top || a.top > b.bottom) return false;

    return true;
}

bool BoxAndPoint(const RECT& box, const Vector2f& p)
{
    if (box.left > (int)p.x || box.right < (int)p.x) return false;
    if (box.top > (int)p.y || box.bottom < (int)p.y) return false;

    return true;
}