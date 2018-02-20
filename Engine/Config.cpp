#include "Config.h"
#include <fstream>

Config::Config(const std::string& filename)
{
	std::ifstream cfg(filename);

	if (cfg)
	{
		for (std::string line; std::getline(cfg, line); )
		{
			if (line == "[Tile Size]")
			{
				int tmp;
				cfg >> tmp;
				if (tmp >= 3 && tmp <= 100)
				{
					tileSize = tmp;
				}
			}
			else if (line == "[Board Size]")
			{
				int tmp;
				int tmp2;
				cfg >> tmp >> tmp2;
				if (tmp >= 5 && tmp <= 500)
				{
					boardWidth = tmp;
				}
				if (tmp2 >= 5 && tmp2 <= 500)
				{
					boardHeight = tmp2;
				}
			}
			else if (line == "[Poison Amount]")
			{
				int tmp;
				cfg >> tmp;
				if (tmp >= 0 && tmp <= 10000)
				{
					poisonAmount = tmp;
				}
			}
			else if (line == "[Goal Amount]")
			{
				int tmp;
				cfg >> tmp;
				if (tmp >= 1 && tmp <= 200)
				{
					goalAmount = tmp;
				}
			}
		}
	}
	cfg.close();
}

int Config::Get(Option option) const
{
	switch (option)
	{
	case Option::TileSize:
		return tileSize;
	case Option::BoardWidth:
		return boardWidth;
	case Option::BoardHeight:
		return boardHeight;
	case Option::PoisonAmount:
		return poisonAmount;
	case Option::GoalAmount:
		return goalAmount;
	default:
		return 0;
	}
}
