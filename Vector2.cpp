#include <iostream>
#include "Vector2.h"

bool Vector2::operator==(Vector2& v)
{
	if (v.x == x && v.y == y)
		return true;
	else
		return false;
}

void Vector2::operator=(Vector2& v)
{
	x = v.x;
	y = v.y;
}

void Vector2::operator=(Vector2&& v)
{
	std::swap(*this, v);
}

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::Vector2(int newX, int newY)
{
	x = newX;
	y = newY;
}

Vector2::Vector2(Vector2& v)
{
	x = v.x;
	y = v.y;
}

Vector2::Vector2(Vector2&& v)
{
	std::swap(*this, v);
}