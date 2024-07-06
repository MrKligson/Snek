#pragma once

#include "Graphics.h"
#include "Location.h"

class Board
{
private:
	struct Border
	{
		int x;
		int y;
		int width;
		int height;
	};

public:
	Board(Graphics& gfx);
	void DrawBorders();
	void DrawCell(Location l, int padding, Color c);
	void TestDrawing(int padding);
	
public:
	static constexpr int rows = 25;
	static constexpr int cols = 35;

private:
	Graphics& gfx;
	const int x;
	const int y;
	Border borders[4];
	static constexpr Color borderColor = Colors::Blue;
	static constexpr int borderWidth = 4;
	static constexpr int borderPadding = 1;
	static constexpr int cellOffset = borderWidth + borderPadding;
	static constexpr int cellSize = 20;
};