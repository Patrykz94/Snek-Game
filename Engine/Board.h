#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>

class Board
{
public:
	Board(Graphics& gfx);
	void DrawBoard();
	void DrawCell(const Location& loc, Color c);
	void DrawObstacle();
	void SpawnObstacle(std::mt19937& rng, const class Snake& snake, const class Goal& goal);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	bool CheckForObstacle(const Location& loc) const;
private:
	static constexpr int dimension = 20;
	static constexpr int width = 39;
	static constexpr int height = 29;
	static constexpr int borderThickness = 5;
	int boardX = (gfx.ScreenWidth - width * dimension) / 2;
	int boardY = (gfx.ScreenHeight - height * dimension) / 2;
	static constexpr Color borderColor = Colors::Gray;
	static constexpr Color obstacleColor = Colors::Gray;
	static constexpr Color boardColor = Colors::MakeRGB(20,20,20);
	bool hasObstacle[width * height] = { false };
	Graphics& gfx;
};