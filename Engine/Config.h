#pragma once
#include <string>

class Config
{
public:
	enum class Option
	{
		TileSize,
		BoardWidth,
		BoardHeight,
		PoisonAmount,
		GoalAmount
	};
public:
	Config(const std::string& filename);
	int Get(Option option) const;
private:
	// Default values
	int tileSize = 20;
	int boardWidth = 39;
	int boardHeight = 29;
	int poisonAmount = 240;
	int goalAmount = 12;
};