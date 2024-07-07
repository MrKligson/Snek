#pragma once

#include "Graphics.h"

class SpriteCodex
{
public:
	static void DrawGameOver(int x, int y, Graphics& gfx);
	static void DrawTitle(int x, int y, Graphics& gfx);
	static constexpr int gameOverWidth = 83;
	static constexpr int gameOverHeight = 63;
	static constexpr int titleWidth = 213;
	static constexpr int titleHeight = 160;
};