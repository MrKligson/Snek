/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	rng(std::random_device()()),
	brd(gfx),
	snek(wnd.kbd, { brd.GetCols() / 2, brd.GetRows() / 2 }),
	target(rng, brd)
{
	target.Respawn(snek, brd);
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	if (!gameStarted) {
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			gameStarted = true;
			wnd.kbd.Flush();
		}
		return;
	}

	if (gameOver) {
		snek.RotateColors();
		return;
	}

	if (snek.IsNotMoving()) {
		return;
	}

	if (!snek.Move(brd)) {
		// board is full or hit border or body
		gameOver = true;
		return;
	}

	if (target.IsAt(snek.GetHeadLocation())) {
		if (!snek.Grow()) {
			// board is full
			gameOver = true;
			return;
		}
		target.Respawn(snek);
	}
}

void Game::ComposeFrame()
{
	if (!gameStarted) {
		SpriteCodex::DrawTitle(titleScreen.x, titleScreen.y, gfx);
		return;
	}

	brd.DrawBorders();
	snek.Draw(brd);
	target.Draw(brd);

	if (gameOver) {
		SpriteCodex::DrawGameOver(gameOverScreen.x, gameOverScreen.y, gfx);
	}
}
