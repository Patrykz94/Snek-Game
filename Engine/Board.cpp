#include "Board.h"
#include "Snake.h"
#include <assert.h>

Board::Board(Graphics & gfx)
	:
	gfx(gfx)
{
}

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

int Board::GetContents(const Location & loc) const
{
	return contents[loc.y * width + loc.x];
}

void Board::ConsumeContents(const Location & loc)
{
	assert(GetContents(loc) == 2 || GetContents(loc) == 3);
	contents[loc.y * width + loc.x] = 0;
}

void Board::SpawnContents(std::mt19937 & rng, const Snake & snake, int contentsType)
{
	std::uniform_int_distribution<int> xDist(0, GetGridWidth() - 1);
	std::uniform_int_distribution<int> yDist(0, GetGridHeight() - 1);

	Location newLoc;
	do
	{
		newLoc.x = xDist(rng);
		newLoc.y = yDist(rng);
	} while (snake.IsInTile(newLoc) || GetContents(newLoc) != 0);

	contents[newLoc.y * width + newLoc.x] = contentsType;
}

void Board::DrawCells()
{
	for (int x = 0; x < width; x++)
	{
		for (int y = 0; y < height; y++)
		{
			if (GetContents({ x,y }) != 0)
			{
				const int contents = GetContents({ x,y });
				if (contents == 1)
				{
					DrawCell({ x,y }, obstacleColor);
				}
				else if (contents == 2)
				{
					DrawCell({ x,y }, foodColor);
				}
				else if (contents == 3)
				{
					DrawCell({ x,y }, cocaineColor);
				}
			}
		}
	}
}
