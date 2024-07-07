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

bool Board::IsValid(const Location& l) const
{
	return l.x >=0 && l.x < cols && l.y >= 0 && l.y < rows;
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
	gfx.DrawRectDim(
		l.x * cellSize + x + cellOffset + padding,
		l.y * cellSize + y + cellOffset + padding,
		drawSize,
		drawSize,
		c
	);
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
