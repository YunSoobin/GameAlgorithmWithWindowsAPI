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
