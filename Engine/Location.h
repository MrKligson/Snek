#pragma once

struct Location
{
	Location(int x, int y) : x(x), y(y) {}
	int x = 0;
	int y = 0;

	bool operator==(const Location& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Location& rhs) const { return x != rhs.x || y != rhs.y; }
	Location operator+(const Location& rhs) const { return { x + rhs.x, y + rhs.y }; }
};