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
	vdist(0, Board::cols - 1),
	hdist(0, Board::rows - 1),
	brd(gfx),
	snek(wnd.kbd, { Board::cols / 2, Board::rows / 2 }),
	target(rng, vdist, hdist)
{
	target.Respawn(snek);
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
		return;
	}

	if (gameOver) {
		snek.RotateColors();
		return;
	}

	if (snek.IsNotMoving()) {
		return;
	}

	Location next = snek.GetNextHeadLocation();
	if (!brd.IsValid(next) || snek.IsInLocation(next, 1)) {
		gameOver = true;
		return;
	}

	snek.Move();

	if (target.IsAt(next)) {
		if (!snek.Grow()) {	// board is full
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
	if (!gameOver) {
		target.Draw(brd);
	}
	else {
		SpriteCodex::DrawGameOver(gameOverScreen.x, gameOverScreen.y, gfx);
	}
}
