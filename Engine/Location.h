#pragma once

struct Location
{
	int x;
	int y;

	bool operator==(const Location& rhs) const { return x == rhs.x && y == rhs.y; }
	bool operator!=(const Location& rhs) const { return x != rhs.x || y != rhs.y; }
	Location operator+(const Location& rhs) const { return { x + rhs.x, y + rhs.y }; }
};