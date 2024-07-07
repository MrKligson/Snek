#pragma once

#include "Graphics.h"
#include "Location.h"
#include <random>
#include <vector>

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
	Board(Graphics& gfx, int nTargets, std::mt19937& rng,
		std::uniform_int_distribution<int>& vdist, std::uniform_int_distribution<int>& hdist);
	bool IsValid(const Location& l) const;
	void DrawBorders();
	void DrawCell(Location l, int padding, Color c);
	int GetObstacleAmount() const;
	static constexpr int GetCellAmount()
	{
		return rows * cols;
	}
	//void TestDrawing(int padding);

	
private:
	static constexpr int rows = 25;
	static constexpr int cols = 35;
	std::vector<Location> obstacles;
	bool hasObstacles = false;
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