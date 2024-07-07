#include "Target.h"

Target::Target(std::mt19937& rng, const Board& brd)
	:
	rng(rng),
	vdist(0, brd.GetCols() - 1),
	hdist(0, brd.GetRows() - 1)
{
}

void Target::Respawn(const Snake& snek, const Board& brd)
{
	do {
		loc = { vdist(rng), hdist(rng) };
	} while (snek.IsInLocation(loc, 0) && !brd.IsValid(loc));
}

bool Target::IsAt(const Location& l) const
{
	return loc == l;
}

void Target::Draw(Board& brd) const
{
	brd.DrawCell(loc, 0, Colors::Red);
}
