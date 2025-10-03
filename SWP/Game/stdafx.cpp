#include "stdafx.h"

Vector2f& Vector2f::operator+=(const Vector2f& other)
{
    this->x += other.x;
    this->y += other.y;

    return *this;
}
