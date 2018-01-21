#include "Board.h"
#include "Snake.h"
#include "Goal.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{}

void Board::DrawBoard()
{
	gfx.DrawBorderDim(boardX, boardY, width * dimension, height * dimension, borderThickness, borderColor);
	for (int x = 0; x < GetGridWidth(); x++)
	{
		for (int y = 0; y < GetGridHeight(); y++)
		{
			gfx.DrawBorderDim(boardX + x * dimension, boardY + y * dimension, dimension, dimension, -1, boardColor);
		}
	}
}

void Board::DrawCell(const Location& loc, Color c)
{
	assert(loc.x >= 0);
	assert(loc.x < width);
	assert(loc.y >= 0);
	assert(loc.y < height);
	gfx.DrawRectDim(loc.x * dimension + 1 + boardX, loc.y * dimension + 1 + boardY, dimension -2, dimension -2, c);
}

void Board::DrawObstacle()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (CheckForObstacle({ x,y }))
			{
				DrawCell({ x,y }, obstacleColor);
			}
		}
	}
}

int Board::GetGridWidth() const
{
	return width;
}

int Board::GetGridHeight() const
{
	return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
	return loc.x >= 0 && loc.x < width &&
		loc.y >= 0 && loc.y < height;
}

bool Board::CheckForObstacle(const Location & loc) const
{
	return hasObstacle[loc.y * width + loc.x];
}

void Board::SpawnObstacle(std::mt19937 & rng, const Snake & snake, const Goal & goal)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || CheckForObstacle(newLoc) || goal.GetLocation() == newLoc);

	hasObstacle[newLoc.y * width + newLoc.x] = true;
}
