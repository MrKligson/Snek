#include "Board.h"
#include <assert.h>

Board::Board(Graphics& gfx)
	:
	gfx(gfx),
	x((gfx.ScreenWidth - cols * cellSize - borderWidth * 2 - borderPadding * 2) / 2),
	y((gfx.ScreenHeight - rows * cellSize - borderWidth * 2 - borderPadding * 2) / 2)
{
	const int height = rows * cellSize + borderPadding * 2;
	const int width = cols * cellSize + borderPadding * 2;

	// top
	borders[0] = { x, y, width + 2 * borderWidth, borderWidth };
	//left
	borders[1] = { x, y + borderWidth, borderWidth, height };
	//right
	borders[2] = { x + borderWidth + width, y + borderWidth, borderWidth, height };
	//bottom
	borders[3] = { x, y + borderWidth + height, width + 2 * borderWidth, borderWidth };
}

Board::Board(Graphics& gfx, int nTargets, std::mt19937& rng)
	:
	Board(gfx)
{
	std::uniform_int_distribution<int> vdist(0, cols);
	std::uniform_int_distribution<int> hdist(0, rows);

	const Location excludeStart = { cols / 2 - 2, rows / 2 - 2 };
	const Location excludeEnd = { cols / 2 + 2, rows / 2 + 2 };

	for (int i = 0; i < nTargets; i++) {
		obstacles.push_back({ vdist(rng), hdist(rng) });

		// make sure we dont spawn to close to the middle:
		while (obstacles[i].x >= excludeStart.x && obstacles[i].x <= excludeEnd.x) {
			obstacles[i].x = vdist(rng);
		}
		while (obstacles[i].y >= excludeStart.y && obstacles[i].y <= excludeEnd.y) {
			obstacles[i].y = vdist(rng);
		}
	}
}

bool Board::IsValid(const Location& l) const
{
	bool valid = l.x >= 0 && l.x < cols && l.y >= 0 && l.y < rows;
	for each (auto obstacle in obstacles) {
		valid = obstacle != l;
	}
	return valid;
}

void Board::DrawBorders()
{
	for each (Border b in borders) {
		gfx.DrawRectDim(b.x, b.y, b.width, b.height, borderColor);
	}
}

void Board::DrawCell(Location l, int padding, Color c)
{
	assert(l.x >= 0 && l.x < cols);
	assert(l.y >= 0 && l.y < rows);
	assert(padding >= 0 && padding < cellSize);

	const int drawSize = cellSize - padding * 2;
	const int offset = cellOffset + padding;
	gfx.DrawRectDim(
		l.x * cellSize + x + offset,
		l.y * cellSize + y + offset,
		drawSize,
		drawSize,
		c
	);
}

int Board::GetCols() const
{
	return cols;
}

int Board::GetRows() const
{
	return rows;
}

int Board::GetObstacleAmount() const
{
	return obstacles.size();
}

//void Board::TestDrawing(int padding) // Draw borders and grid in same color
//{
//	DrawBorders();
//
//	Location l = { 0,0 };
//	for (l.y = 0; l.y < rows; l.y++) {
//		for (l.x = 0; l.x < cols; l.x++) {
//			DrawCell(l, padding, borderColor);
//		}
//	}
//}
