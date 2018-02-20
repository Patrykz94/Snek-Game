#include "Snake.h"
#include <assert.h>

Snake::Snake(const Location & loc)
{
	segments.push_back(loc);
}

void Snake::MoveBy(const Location & delta_loc)
{
	for (int i = segments.size() - 1; i > 0; i--)
	{
		segments[i].Follow(segments[i - 1]);
	}
	segments.front().MoveBy(delta_loc);
}

Location Snake::GetNextHeadLocation(const Location & delta_loc) const
{
	Location l(segments.front().GetLocation());
	l.Add(delta_loc);
	return l;
}

void Snake::Grow()
{
	segments.push_back(bodyColors[segments.size() % bodyColors.size()]);
}

void Snake::Draw(Board & brd) const
{
	for (unsigned int i = 0; i < segments.size(); i++)
	{
		segments[i].Draw(brd);
	}
}

bool Snake::IsInTile(const Location & target) const
{
	for (unsigned int i = 0; i < segments.size(); i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

bool Snake::IsInTileExceptEnd(const Location & target) const
{
	for (unsigned int i = 0; i < segments.size() - 1; i++)
	{
		if (segments[i].GetLocation() == target)
		{
			return true;
		}
	}
	return false;
}

int Snake::GetLenght() const
{
	return segments.size();
}

Snake::Segment::Segment(Color c)
{
	InitBody(c);
}

Snake::Segment::Segment(Location loc)
{
	InitHead(loc);
}

void Snake::Segment::InitHead(const Location & in_loc)
{
	loc = in_loc;
	c = Snake::headColor;
}

void Snake::Segment::InitBody(Color c_in)
{
	c = c_in;
}

void Snake::Segment::Follow(const Segment & next)
{
	loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
	assert(abs(delta_loc.x) + abs(delta_loc.y) == 1);
	loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd) const
{
	brd.DrawCell(loc, c);
}

const Location& Snake::Segment::GetLocation() const
{
	return loc;
}
