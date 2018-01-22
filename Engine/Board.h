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
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	int GetContents(const Location& loc) const;
	void ConsumeContents(const Location& loc);
	void SpawnContents(std::mt19937& rng, const class Snake& snake, int contentsType);
	void DrawCells();
private:
	static constexpr int dimension = 20;
	static constexpr int width = 39;
	static constexpr int height = 29;
	static constexpr int borderThickness = 5;
	int boardX = (gfx.ScreenWidth - width * dimension) / 2;
	int boardY = (gfx.ScreenHeight - height * dimension) / 2;
	static constexpr Color borderColor = Colors::MakeRGB(100, 100, 100);
	static constexpr Color obstacleColor = Colors::MakeRGB(100, 100, 100);
	static constexpr Color foodColor = Colors::Red;
	static constexpr Color cocaineColor = Colors::White;
	static constexpr Color boardColor = Colors::MakeRGB(20,20,20);
	// 0:empty 1:obstacle 2:food 3:cocaine-speedup
	int contents[width * height] = { 0 };
	Graphics& gfx;
};