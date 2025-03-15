#pragma once

class Vector2 {
public:
	int x;
	int y;
	Vector2();
	Vector2(int newX, int newY);
	Vector2(Vector2& v);
	Vector2(Vector2&& v);
	bool operator== (Vector2& v);
	void operator= (Vector2& v);
	void operator= (Vector2&& v);
};