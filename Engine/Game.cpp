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
	snek(wnd.kbd, brd),
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
	state = Game::Won;

	switch (state) {
	case Game::Started:
		break;
	case Game::Waiting:
		if (wnd.kbd.KeyIsPressed(VK_RETURN)) {
			state = Started;
			wnd.kbd.Flush();
		}
		return;
	case Game::Won:
		snek.RotateColors();
	case Game::GameOver:
		return;
	default:
		break;
	}

	if (!snek.IsPreparingToMove()) {
		return;
	}

	if (!snek.Move(brd)) {
		state = Game::GameOver;
		return;
	}

	if (target.IsAt(snek.GetHeadLocation())) {
		snek.Grow();
		if (!snek.CanGrow()) {
			state = Game::Won;
			return;
		}
		target.Respawn(snek, brd);
	}
}

void Game::ComposeFrame()
{
	if (state == Game::Waiting) {
		SpriteCodex::DrawTitle(titleScreen.x, titleScreen.y, gfx);
		return;
	}

	brd.DrawBorders();
	snek.Draw(brd);
	target.Draw(brd);

	if (state == Game::GameOver || state == Game::Won) {
		SpriteCodex::DrawGameOver(gameOverScreen.x, gameOverScreen.y, gfx);
	}
}
