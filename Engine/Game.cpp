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
#include "SpriteCodex.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	brd(gfx),
	rng(std::random_device()()),
	snek({ 2,2 }),
	goal(rng, brd, snek)
{
	snekMovePeriod = 20;
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
	const float dt = ft.Mark();

	if (!gameIsOver) {
		if (gameIsStarted)
		{
			if (wnd.kbd.KeyIsPressed(VK_UP))
			{
				if (snek.GetLenght() == 1 || delta_loc.y != 1)
				{
					delta_loc = { 0, -1 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_DOWN))
			{
				if (snek.GetLenght() == 1 || delta_loc.y != -1)
				{
					delta_loc = { 0, 1 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_LEFT))
			{
				if (snek.GetLenght() == 1 || delta_loc.x != 1)
				{
					delta_loc = { -1, 0 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_RIGHT))
			{
				if (snek.GetLenght() == 1 || delta_loc.x != -1)
				{
					delta_loc = { 1, 0 };
				}
			}
			if (wnd.kbd.KeyIsPressed(VK_SPACE))
			{
				snekSupercharge = true;
			}
			else {
				snekSupercharge = false;
			}

			++snekMoveCounter;
			if (snekMoveCounter >= snekMovePeriod || snekSupercharge && snekMoveCounter >= snekMovePeriod / 2)
			{
				snekMoveCounter = 0;
				const Location next = snek.GetNextHeadLocation(delta_loc);
				if (!brd.IsInsideBoard(next) ||
					snek.IsInTileExceptEnd(next))
				{
					gameIsOver = true;
				}
				else
				{
					bool eating = next == goal.GetLocation();
					if (eating)
					{
						snek.Grow();
					}
					snek.MoveBy(delta_loc);
					if (eating)
					{
						goal.Respawn(rng, brd, snek);
						if (snekMovePeriod > 10)
						{
							if (snek.GetLenght() % 5 == 4)
							{
								snekMovePeriod--;
							}
						}
					}
				}
			}
		}
		else if (wnd.kbd.KeyIsPressed(VK_RETURN))
		{
			gameIsStarted = true;
		}
	}
}

void Game::ComposeFrame()
{
	brd.DrawBoard();
	goal.Draw(brd);
	snek.Draw(brd);
	if (gameIsOver)
	{
		SpriteCodex::DrawGameOver(350, 250, gfx);
	}
	else if (!gameIsStarted)
	{
		SpriteCodex::DrawTitle(300, 200, gfx);
	}
}