#pragma once
#include "Graphics.h"
#include "Location.h"
#include <random>
#include "Config.h"
#include <vector>

class Board
{
public:
	enum class CellContents : char
	{
		Empty,
		Obstacle,
		Food,
		Cocaine
	};
public:
	Board(Graphics& gfx, const Config& config);
	void DrawBoard();
	void DrawCell(const Location& loc, Color c);
	int GetGridWidth() const;
	int GetGridHeight() const;
	bool IsInsideBoard(const Location& loc) const;
	CellContents GetContents(const Location& loc) const;
	void ConsumeContents(const Location& loc);
	void SpawnContents(std::mt19937& rng, const class Snake& snake, CellContents contentsType);
	void DrawCells();
private:
	int dimension;
	int width;
	int height;
	static constexpr int borderThickness = 5;
	int boardX = (gfx.ScreenWidth - width * dimension) / 2;
	int boardY = (gfx.ScreenHeight - height * dimension) / 2;
	static constexpr Color borderColor = Colors::MakeRGB(100, 100, 100);
	static constexpr Color obstacleColor = Colors::MakeRGB(100, 100, 100);
	static constexpr Color foodColor = Colors::Red;
	static constexpr Color cocaineColor = Colors::White;
	static constexpr Color boardColor = Colors::MakeRGB(20,20,20);
	std::vector<CellContents> contents;
	Graphics& gfx;
};